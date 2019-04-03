#include "Drag.h"
#include <glm\glm.hpp>

void Drag::updateForce(PhysicsParameters * Parameters, float dt)
{
	vec2 drag = Parameters->Velocity;
	float dragCoeff = length(drag);
	dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;
	drag = -dragCoeff * normalize(drag);
	Parameters->AddForce(drag);
}
