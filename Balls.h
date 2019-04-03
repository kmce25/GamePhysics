#pragma once
#include <glm\glm.hpp>
#include <GL/glut.h>
#include <glm\gtc\constants.hpp>
#include "PhysicsEntity.h"
#include "BoundingSphere.h"


using namespace std;
using namespace glm;

class Balls : public PhysicsEntity
{
private:
	float Radius;
	vec3 Color;

public:
	Balls(float radius, PhysicsParameters* Parameters, vec3 color = vec3(0, 1, 1))		// (vec3 color = vec3(0,1,1)) is a optional parameter. If colour is passed when constructor called, that colour will be used, if not, the pre defined colour will be used
		: Radius(radius), Color(color)
	{
		Balls::Parameters = Parameters;
		collider = new BoundingSphere(Balls::Radius, Parameters->transform.getPosition());
	}

	virtual ~Balls() {}
	
	void update(float dt);
	void Draw(int width, int height);
};