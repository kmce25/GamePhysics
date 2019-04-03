#pragma once
#include <glm\glm.hpp>
#include "PhysicsParameters.h"
#include "Force.h"

class Gravity : public Force
{
private:
	const vec2 gravity;
public:
	Gravity(const vec2& gravity)
		: gravity(gravity)
	{

	}
	virtual ~Gravity() {}
	void updateForce(PhysicsParameters *object, float dt);
};