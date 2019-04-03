#pragma once
#include <glm\glm.hpp>
#include <GL/glut.h>
#include "PhysicsEntity.h"
#include "Transform.h"
#include "AABB.h"

using namespace std;

class Cushions : public PhysicsEntity
{
private:
	vec2 radius;
	vec3 color;
	vec2 center;

public:
	Cushions(vec2 Radius, vec2 center, PhysicsParameters* Parameters, vec3 color = vec3(1, 1, 0))
			: radius(Radius), color(color)
	{
		Cushions::Parameters = Parameters;
		collider = new AABB(Cushions::radius, Parameters->transform);		//Parameters->transform.getPosition() //// new AABB(Cushions::radius, center);
	}
	virtual ~Cushions() {};

	void update(float dt);
	void Draw(int width, int height);
};

/*

Cushions::Parameters = Parameters;
collider = new AABB(Cushions::radius, Parameters->transform.getPosition());

*/