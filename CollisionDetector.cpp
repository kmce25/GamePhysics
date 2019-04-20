// (c) Marco Gilardi, 2017
#include "CollisionDetector.h"
#include "Utils.h"
#include "BoundingSphere.h"
#include "AABB.h"
#include<vector>
#include <iostream>
#include "BoundingSpherePocket.h"

using namespace std;
using namespace glm;

CollisionData* CollisionDetector::CheckCollision(PhysicsEntity* obj1, PhysicsEntity* obj2)
{
	CollisionData* data = nullptr;

	if (dynamic_cast<BoundingSphere*>(obj1->getCollider()) != nullptr && dynamic_cast<BoundingSphere*>(obj2->getCollider()) != nullptr)
	{
		CollisionDetector::SphereSphereCollision(obj1, obj2, &data);
		return data;
	}
	
	if ((dynamic_cast<BoundingSphere*>(obj1->getCollider()) != nullptr && dynamic_cast<AABB*>(obj2->getCollider()) != nullptr) || 
		(dynamic_cast<AABB*>(obj1->getCollider()) != nullptr && dynamic_cast<BoundingSphere*>(obj2->getCollider()) != nullptr))
	{
		CollisionDetector::SphereAABBCollision(obj1, obj2, &data);
		return data;
	}

	if (dynamic_cast<AABB*>(obj1->getCollider()) != nullptr && dynamic_cast<AABB*>(obj2->getCollider()) != nullptr)
	{
		CollisionDetector::AABBAABBCollision(obj1, obj2, &data);
		return data;
	}

	if ((dynamic_cast<BoundingSphere*>(obj1->getCollider()) != nullptr && dynamic_cast<BoundingSpherePocket*>(obj2->getCollider()) != nullptr) ||
		(dynamic_cast<BoundingSpherePocket*>(obj1->getCollider()) != nullptr && dynamic_cast<BoundingSphere*>(obj2->getCollider()) != nullptr))
	{
		CollisionDetector::SpherePocketCollision(obj1, obj2, &data);
		return data;
	}

	return data;
}

bool CollisionDetector::SphereSphereCollision(PhysicsEntity * obj1, PhysicsEntity * obj2, CollisionData** data) // we need to fill data so we need to pass a pointer to pointer
{
	BoundingSphere* s1 = dynamic_cast<BoundingSphere*>(obj1->getCollider());
	BoundingSphere* s2 = dynamic_cast<BoundingSphere*>(obj2->getCollider());
	
	float dist = Utils::distanceBetweenPoints(s1->getCenter(), s2->getCenter());
	float penetration = dist - (s1->getRadii() + s2->getRadii());
	bool collision = penetration <= 0;
	if (collision)
	{
		*data = new CollisionData();
		(*data)->maxNumContacts = 1;
		(*data)->numContactsLeft = (*data)->maxNumContacts;
		(*data)->contact = new Contact[(*data)->maxNumContacts];

		(*data)->contact[0].SetObjects(vector<PhysicsEntity*> { obj1, obj2 });
		(*data)->contact[0].SetContactNormal(normalize(obj1->GetParameters()->transform.getPosition() - obj2->GetParameters()->transform.getPosition()));
		(*data)->contact[0].SetRestitution(0.5f*(obj1->GetParameters()->GetRestitution() + obj2->GetParameters()->GetRestitution()));

		(*data)->contact[0].SetPenetration(penetration);
		(*data)->numContactsLeft--;
	}

	return collision;
}

bool CollisionDetector::SphereAABBCollision(PhysicsEntity * obj1, PhysicsEntity * obj2, CollisionData** data)
{
	AABB* aabb;
	BoundingSphere* s = dynamic_cast<BoundingSphere*>(obj1->getCollider());
	if (s != nullptr)
		aabb = dynamic_cast<AABB*>(obj2->getCollider());
	else
	{
		aabb = dynamic_cast<AABB*>(obj1->getCollider());
		s = dynamic_cast<BoundingSphere*>(obj2->getCollider());
	}

	vec2 pointOnAABB = Utils::projectPointOnAABB(s->getCenter(), aabb);
	float dist = Utils::distanceBetweenPoints(s->getCenter(), pointOnAABB);
	float penetration = dist - s->getRadii();
	bool collision = penetration <= 0;
	if (collision)
	{
		*data = new CollisionData();
		(*data)->maxNumContacts = 1;
		(*data)->numContactsLeft = (*data)->maxNumContacts;
		(*data)->contact = new Contact[(*data)->maxNumContacts];

		(*data)->contact[0].SetObjects(vector<PhysicsEntity*> { obj1, obj2 });
		if (obj1->GetParameters()->GetInverseMass() < obj2->GetParameters()->GetInverseMass())
		{
			(*data)->contact[0].SetObjects(vector<PhysicsEntity*> { obj2, obj1 });
			(*data)->contact[0].SetContactNormal(Utils::getAABBFaceNormal(s->getCenter(), aabb));
		}
		else
		{
			(*data)->contact[0].SetObjects(vector<PhysicsEntity*> { obj1, obj2 });
			(*data)->contact[0].SetContactNormal(-Utils::getAABBFaceNormal(s->getCenter(), aabb));
		}
		(*data)->contact[0].SetRestitution(0.5f * (obj1->GetParameters()->GetRestitution() + obj2->GetParameters()->GetRestitution()));

		(*data)->contact[0].SetPenetration(penetration);
		(*data)->numContactsLeft--;
	}

	return collision;
}


bool CollisionDetector::AABBAABBCollision(PhysicsEntity * obj1, PhysicsEntity * obj2, CollisionData** data)
{
	AABB* aabb1 = dynamic_cast<AABB*>(obj1->getCollider());
	AABB* aabb2 = dynamic_cast<AABB*>(obj2->getCollider());

	vec2 aabb1ProjCenterX = aabb1->getCenter().x*Utils::right;
	vec2 aabb2ProjCenterX = aabb2->getCenter().x*Utils::right;
	float distX = Utils::distanceBetweenPoints(aabb1ProjCenterX, aabb2ProjCenterX);
	float penetrationX = distX - (aabb1->getRadii().x + aabb2->getRadii().x);
	bool collisionX = penetrationX <= 0;

	vec2 aabb1ProjCenterY = aabb1->getCenter().y*Utils::up;
	vec2 aabb2ProjCenterY = aabb2->getCenter().y*Utils::up;
	float distY = Utils::distanceBetweenPoints(aabb1ProjCenterY, aabb2ProjCenterY);
	float penetrationY = distY - (aabb1->getRadii().y + aabb2->getRadii().y);
	bool collisionY = penetrationY <= 0;
	bool collision = collisionX && collisionY;

	if (collision)
	{
		*data = new CollisionData();
		(*data)->maxNumContacts = 1;
		(*data)->numContactsLeft = (*data)->maxNumContacts;
		(*data)->contact = new Contact[(*data)->maxNumContacts];

		vec2 point = aabb1->getCenter();
		AABB* aabb = aabb2;

		vec2 normal = -Utils::getAABBFaceNormal(point, aabb);
		if (obj1->GetParameters()->GetInverseMass() < obj2->GetParameters()->GetInverseMass())
		{
			point = aabb2->getCenter();
			aabb = aabb1;
			(*data)->contact[0].SetObjects(vector<PhysicsEntity*> { obj2, obj1 });
		}
		else
		{
			normal = Utils::getAABBFaceNormal(point, aabb);
			(*data)->contact[0].SetObjects(vector<PhysicsEntity*> { obj1, obj2 });
		}
		(*data)->contact[0].SetContactNormal(normal);

		(*data)->contact[0].SetRestitution(0.5f * (obj1->GetParameters()->GetRestitution() + obj2->GetParameters()->GetRestitution()));

		vec2 penetrations = vec2(penetrationX, penetrationY);
		float penetration = dot(penetrations, abs(normal));
		(*data)->contact[0].SetPenetration(penetration);
		(*data)->numContactsLeft--;
	}

	return collision;
}

bool CollisionDetector::SpherePocketCollision(PhysicsEntity * obj1, PhysicsEntity * obj2, CollisionData** data)
{
BoundingSpherePocket* bs1 = dynamic_cast<BoundingSpherePocket*>(obj1->getCollider());								
BoundingSphere* bs2 = dynamic_cast<BoundingSphere*>(obj2->getCollider());
	/*if (bs1 != nullptr)
	{*/

		float dist = Utils::distanceBetweenPoints(bs1->getCenter(), bs2->getCenter());	//bs2 returning as a nullptr, the information does not seem to be getting passed to it, center etc. 
		float penetration = dist - (bs1->getRadii() + bs2->getRadii());
		bool collision = penetration <= 0;
		if (collision)
		{
			delete obj1;
		}

		return collision;
	/*}*/
}


///DOES NOT RETURN NULLPTR BUT THROUGHS READING VIOLAITON
//BoundingSpherePocket* bs1 = dynamic_cast<BoundingSpherePocket*>(obj1->getCollider());								
//BoundingSphere* bs2 = dynamic_cast<BoundingSphere*>(obj2->getCollider());


///RETURNS NULLPTR BUT DOES NOT THROUGH READING VIOLATION
//BoundingSphere* bs1 = dynamic_cast<BoundingSphere*>(obj1->getCollider());								
//BoundingSpherePocket* bs2 = dynamic_cast<BoundingSpherePocket*>(obj2->getCollider());

///
//BoundingSphere* bs1;
//BoundingSpherePocket* bs2 = dynamic_cast<BoundingSpherePocket*>(obj1->getCollider());
//if (bs2 != nullptr)
//bs1 = dynamic_cast<BoundingSphere*>(obj2->getCollider());
//else
//{
//	bs1 = dynamic_cast<BoundingSphere*>(obj1->getCollider());
//	bs2 = dynamic_cast<BoundingSpherePocket*>(obj2->getCollider());
//}