#pragma once
#include <glm\glm.hpp>
#include <GL/glut.h>
#include "Object.h"
#include "Transform.h"
using namespace std;

class Shadow : public Object
{
private:
	vec2 radius;
	vec3 color;
	void update(float dt);
	void Draw(int width, int height);
	Transform transform;
	vec2 centre;
	void move(vec2 traslation);

public:
	Shadow(vec2 Radius, vec2 centre) : radius(Radius)
	{
		move(centre);
	}
	virtual ~Shadow() {};

	vec2 getPosition();
	vec2 getRadius();
	void setColor(float r, float g, float b);


};