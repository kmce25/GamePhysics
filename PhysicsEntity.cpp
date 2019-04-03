#include "PhysicsEntity.h"

void PhysicsEntity::SetParameters(PhysicsParameters * Parameters)
{
	PhysicsEntity::Parameters = Parameters;
}

PhysicsParameters * PhysicsEntity::GetParameters()
{
	return Parameters;
}

Collider * PhysicsEntity::getCollider()
{
	return collider;
}
