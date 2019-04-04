// (c) Marco Gilardi, 2017
#include "BoundingSpherePocket.h"
#include "AABB.h"
#include "CollisionDetector.h"
#include <iostream>
using namespace std;

float BoundingSpherePocket::getRadii() const
{
	return radius;
}

const vec2 BoundingSpherePocket::getCenter() const
{
	return center;
}

void BoundingSpherePocket::update(const Transform& transform)
{
	center = transform.getPosition();
}
