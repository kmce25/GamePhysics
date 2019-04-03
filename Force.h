//This class allows for the creation of other types of forces by defining new classes that inherit from this class
#pragma once
#include "PhysicsParameters.h"

class Force																		//Force abstract class describes the core methods that every force concrete class should have
{
public:
	virtual ~Force() {}
	virtual void updateForce(PhysicsParameters *object, float dt) = 0;			//Pure Virtual function = 0
};