#include <iostream>
#include "Table.h"
#include "Transform.h"

using namespace std;


void Table::update(float dt)
{

}

void Table::move(vec2 traslation)
{
	transform.Translate(traslation);
}

void Table::Draw(int width, int height)
{

	vec2 position = transform.getPosition();

	glLoadIdentity();				
	float aspectRatio = (width / (float)height);
	glTranslatef(aspectRatio * (position.x - (0.5f * width)) / (0.5f * width),
		(position.y - (0.5f * height)) / (0.5f * height), 0.0f);  

	glBegin(GL_QUADS);
	glColor3f(color.r, color.g, color.b);
	glVertex2f(2 * radius.x * aspectRatio / width, 2 * radius.y / height);
	glVertex2f(-2 * radius.x * aspectRatio / width, 2 * radius.y / height);
	glVertex2f(-2 * radius.x * aspectRatio / width, -2 * radius.y / height);
	glVertex2f(2 * radius.x * aspectRatio / width, -2 * radius.y / height);
	glEnd();
}

void Table::setColor(float r, float g, float b)
{
	color = vec3(r, g, b);
}

vec2 Table::getPosition()
{
	return transform.getPosition();
}

vec2 Table::getRadius()
{
	return radius;
}