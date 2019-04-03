#pragma once
#include "glm\glm.hpp"
#include <vector>

using namespace std;
using namespace glm;

class PhysicsEntity;

class Contact
{
//private:
//	void ResolveVelocity(float dt);
//	void ResolveInterpenetration(float dt);
//	float ResolveRestingContact(float dt);
//
//public:
//
//	float Restitution;
//	float Penetration;
//	vec2 ContactNormal;
//	vector<PhysicsEntity*> obj;
//	void Resolve(float dt);
//	float ComputeSeparatingVelocity() const;
//	void SetObjects(const vector<PhysicsEntity*>& objects);		//void SetObjects(vector<PhysicsEntity*>& objects);
//	void SetRestitution(float rest);
//	void SetPenetration(float penetration);
//	void SetContactNormal(vec2 normal);					//void SetContactNormal(vec2 &normal);	

private:
		float Restitution;
		float Penetration;
		vec2 ContactNormal;
		void ResolveVelocity(float dt);
		float ResolveRestingContact(float dt);
public:
	void ResolveInterpenetration(float dt);
	void SetContactNormal(const vec2 &normal);							//void SetContactNormal(vec2 &normal);	FOR normalize in CollisionDectector
	void SetObjects(const vector<PhysicsEntity*>& objects);
	void SetRestitution(float rest);
	void SetPenetration(float penetration);
	float ComputeSeparatingVelocity() const;
	void Resolve(float dt);
	vector<PhysicsEntity*> obj;
};