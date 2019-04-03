#pragma once
#include "Entity.h"
#include "PhysicsParameters.h"
#include "Collider.h"

class PhysicsEntity : public Entity
{
protected:
	PhysicsParameters* Parameters = nullptr;					// Pointer parameters to the PhysicsParameters
	Collider* collider = nullptr;
private:
	float Restitution;
public:
	PhysicsEntity()
	{

	}

	virtual ~PhysicsEntity()
	{
		if (Parameters != nullptr)
			delete Parameters;
		if (collider != nullptr)
			delete collider;
	}
																//Virtual functions are used by the children 
	virtual void update(float dt) = 0;							//update physics of the object			
	virtual void Draw(int width, int height) = 0;				//Draw objects

	void SetParameters(PhysicsParameters* Parameters);			//Sets the physics parameters to that of the parameters passed in?
	PhysicsParameters* GetParameters();							//Returns parameters of the object
	Collider* getCollider();
};