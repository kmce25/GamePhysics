#pragma once
#include <iostream>
#include <glm\glm.hpp>
#include <GL\glut.h>
#include "Transform.h"
#include "Object.h"


using namespace std;
using namespace glm;

class Table : public Object
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
	Table(vec2 Radius, vec2 centre) 
		: radius(Radius)
	{
		move(centre);
	}
	virtual ~Table() {};

	vec2 getPosition();
	vec2 getRadius();
	void setColor(float r, float g, float b);

};