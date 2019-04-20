#pragma once
#include "Collider.h"
#include "glm\glm.hpp"

using namespace glm;

class BoundingSpherePocket : public Collider
{
private:
	float radius;
	vec2 center;

public:
	BoundingSpherePocket(float radius, const vec2& centre)
		: radius(radius), center(centre)
	{

	}
	virtual ~BoundingSpherePocket() {}

	const vec2 getCenter() const;

	void update(const Transform& transform);

	float getRadii() const;
};
