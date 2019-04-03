#pragma once
// (c) Marco Gilardi, 2017

// Making this class static is a design choice, there are better choices using patterns. However,
// I did not want to overcomplicate this example as the point is showing how things interact not
// implementing patterns.
#include "glm\glm.hpp"
#include "PhysicsEntity.h"
#include "CollisionData.h"

class BoundingSphere;
class AABB;

using namespace glm;

class CollisionDetector
{
public:
	CollisionDetector() {}
	virtual ~CollisionDetector() {}
	static	CollisionData* CheckCollision(PhysicsEntity* obj1, PhysicsEntity* obj2);
private:
	static bool SphereSphereCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data);

	static bool SphereAABBCollision(PhysicsEntity* obj1,  PhysicsEntity* obj2, CollisionData** data);
	static bool AABBAABBCollision(PhysicsEntity* obj1,  PhysicsEntity* obj2, CollisionData** data);
};
