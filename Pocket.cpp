#include <iostream>
#include "Pocket.h"

using namespace std;

void Pockets::Draw(int width, int height)
{
	vec2 position = transform.getPosition();
	glLoadIdentity();				
	float aspectRatio = (width / (float)height);
	glTranslatef(aspectRatio * (position.x - (0.5f * width)) / (0.5f * width),
		(position.y - (0.5f * height)) / (0.5f * height), 0.0f);  

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(color.r, color.g, color.b);						
	glVertex2f(0.0f, 0.0f);										
	int numSegments = 100;
	float angle;
	for (int i = 0; i <= numSegments; i++) {					
		angle = i * 2.0f * pi<float>() / numSegments;			
		glVertex2f(cos(angle) * (2.0f * Radius / width)* aspectRatio,
			sin(angle) * (2.0f * Radius / height));
	}
	glEnd();
}

void Pockets::move(vec2 traslation)
{
	transform.Translate(traslation);
}

void Pockets::setColor(float r, float g, float b)
{
	color = vec3(r, g, b);
}

vec2 Pockets::getPosition()
{
	return transform.getPosition();
}

float Pockets::getRadius()
{
	return Radius;
}

void Pockets::update(float dt)
{

}
