// (c) Marco Gilardi, 2017
#pragma once
#include "Collider.h"
#include "Contact.h"
#include "glm\glm.hpp"

using namespace glm;

class AABB : public Collider
{
private:
	vec2 radius;
	vec2 center;
	Collider* C;
public:
	AABB(vec2& radius, const Transform& transform)			//AABB(vec2& radius, const vec2& center) : radius(radius), center(center)
		: radius(radius), center(transform.getPosition())
	{
	
	};
	virtual ~AABB() {};
	void update(const Transform& transform);

	const vec2 getCenter() const;
	const vec2 getRadii() const;
};
/*
AABB(vec2& radius, const vec2& center)
: radius(radius), center(center)
*/