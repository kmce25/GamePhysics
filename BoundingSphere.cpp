// (c) Marco Gilardi, 2017
#include "BoundingSphere.h"
#include "AABB.h"
#include "CollisionDetector.h"
#include <iostream>
using namespace std;

float BoundingSphere::getRadii() const
{
	return radius;
}

const vec2 BoundingSphere::getCenter() const
{
	return center;
}

void BoundingSphere::update(const Transform& transform)
{
	center = transform.getPosition();
}
