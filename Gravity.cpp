#include "Gravity.h"
#include "PhysicsParameters.h"

void Gravity::updateForce(PhysicsParameters *object, float dt)
{
	object->AddForce(gravity * object->GetMass());			//Adding force to object, by gravity * mass
}

//Inital value of reference to non const must be an Ivalue