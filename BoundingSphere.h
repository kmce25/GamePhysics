#pragma once
#include "Collider.h"
#include "glm\glm.hpp"

using namespace glm;

class BoundingSphere : public Collider
{
private:
	float radius;
	vec2 center;

public:
	BoundingSphere(float radius, const vec2& centre)
		: radius(radius), center(centre) 
	{
	
	}
	virtual ~BoundingSphere() {}

	const vec2 getCenter() const;

	void update(const Transform& transform);

	float getRadii() const;
};
