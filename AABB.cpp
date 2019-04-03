// (c) Marco Gilardi, 2017
#include "AABB.h"
#include "BoundingSphere.h"
#include "CollisionDetector.h"
#include "Utils.h"

const vec2 AABB::getCenter() const
{
	return center;
}

const vec2 AABB::getRadii() const
{
	return radius;
}

void AABB::update(const Transform& transform)
{
	center = transform.getPosition();
}