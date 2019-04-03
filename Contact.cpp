#include "Contact.h"
#include "PhysicsEntity.h"

void Contact::ResolveVelocity(float dt)
{																									//Computes impulse
	float separatingVelocity = ComputeSeparatingVelocity();											//separatingVelocity = computeSeparatingVelocity which is calculated above
	if (separatingVelocity > 0) return;																//If separatingVelocity > 0 quit, else :
	float newSepVel = -separatingVelocity * (1 + Restitution) + ResolveRestingContact(dt);			//Compute new seperating velocity

	if (newSepVel < 0) newSepVel = 0;
	float totalInvMass = obj[0]->GetParameters()->GetInverseMass();									//Total mass = all objects mass

	if (obj[1])																						//If object exists:	
		totalInvMass += obj[1]->GetParameters()->GetInverseMass();									//Add objects mass to total mass
	if (totalInvMass < 0) return;
	float impulseLenght = newSepVel / totalInvMass;
	vec2 impulse = impulseLenght * ContactNormal;													//Compute the impulse (contact normal should be normalised already)
																									
																									//Applies the impulse
	obj[0]->GetParameters()->Velocity = obj[0]->GetParameters()->Velocity + impulse * obj[0]->GetParameters()->GetInverseMass();				//Add the computed impulse to the objects velocity
	if (obj[1])
		obj[1]->GetParameters()->Velocity = obj[1]->GetParameters()->Velocity - impulse * obj[1]->GetParameters()->GetInverseMass();			//Add the computed impulse to the objects velocity (-impluse since the object moves in opposite direction)
}

void Contact::ResolveInterpenetration(float dt)
{

	if (Penetration <= 0) return;																					//If penetration < 0 - finish, if >0 continue
	float totalInvMass = obj[0]->GetParameters()->GetInverseMass();													// Total all = mass of every object 
	if (obj[1]) totalInvMass += obj[1]->GetParameters()->GetInverseMass();											// If a object exists, add object mass to total mass ((obj[1]) = check object exists)
	if (totalInvMass <= 0) return;																					// If total mass < 0 - finish, if > 0 continue

	vec2 movePerUnitMass = ContactNormal * (-Penetration / totalInvMass);											//Determines how much objects move after collision. Heavier mass = less movement. ((m2/m1+m2) *d * n) d = penetration

	obj[0]->GetParameters()->transform.Translate(movePerUnitMass * obj[0]->GetParameters()->GetInverseMass());		//Get position of object, and move object position by movePerUnitMass * objects mass
	if (obj[1])																										// if object exists
		obj[1]->GetParameters()->transform.Translate(movePerUnitMass * obj[1]->GetParameters()->GetInverseMass());	//Get position of object, and move object position by movePerUnitMass * objects mass
}

float Contact::ResolveRestingContact(float dt)
{
	vec2 accCausedVel = obj[0]->GetParameters()->Acceleration;														//accCausedVel = objects acceleration
	if (obj[1]) accCausedVel += obj[1]->GetParameters()->Acceleration;												//If object exists, add object 2 acceleration to accCausedVel
	float accCausedSepVel = dot(accCausedVel, ContactNormal)*dt;													//accCausedSepVel = seperating velocity due to acceleration. *dt because it is an acceleration, not velocity
	if (accCausedSepVel < 0)																						//If accCausedSepVel < 0, object must move
	{
		return Restitution * accCausedSepVel;																		//Amount object must move
	}
	else
		return 0;
}

void Contact::Resolve(float dt)
{
	ResolveVelocity(dt);																							// Call resolveVelocity
	ResolveInterpenetration(dt);																					// Call resolveInterpenetration
}

float Contact::ComputeSeparatingVelocity() const
{
	vec2 relVelocity = obj[0]->GetParameters()->Velocity;								//Get velocity of a object
	if (obj[1]) relVelocity -= obj[1]->GetParameters()->Velocity;						//If object exists, get velocity and remove the velocity of this object from the first object
	return dot(relVelocity, ContactNormal);												// Returns the closing velocity . (V2-V2 * n). Closing velocity = velocity of the two objects moving towards each other(along the contact normal)
}																						// if > 0 : bodies are separating. if = 0 : contact. if <0 : bodies are getting closer

void Contact::SetObjects(const vector<PhysicsEntity*>& objects)
{
	obj = objects;
}

void Contact::SetRestitution(float rest)
{
	Restitution = rest;
}

void Contact::SetPenetration(float penetration)
{
	Penetration = penetration;
}

void Contact::SetContactNormal(const vec2 &normal)				//void Contact::SetContactNormal(vec2 &normal)
{
	ContactNormal = normal;
}
