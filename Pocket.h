#pragma once
#include <glm/glm.hpp>
#include <GL\glut.h>
#include <iostream>
#include "Transform.h"
#include "Object.h"
#include <glm\gtc\constants.hpp>

using namespace glm;
using namespace std;

class Pockets : public Object
{
private:
	float Radius;
	vec3 color;
	void Draw(int width, int height);
	void move(vec2 traslation);
	Transform transform;
	void update(float dt);

public:
	Pockets(float radius, vec2 pos) 
		: color(vec3(0.0f, 0.0f, 0.0f)), Radius(radius)
	{
		move(pos);
	}
	virtual ~Pockets() {}

	vec2 getPosition();
	float getRadius();
	void setColor(float r, float g, float b);
};