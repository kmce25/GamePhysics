#include "Shadow.h"

vec2 Shadow::getPosition()
{
	return transform.getPosition();
}

vec2 Shadow::getRadius()
{
	return radius;
}

void Shadow::update(float dt)
{
}

void Shadow::Draw(int width, int height)
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

void Shadow::move(vec2 traslation)
{
	transform.Translate(traslation);
}

void Shadow::setColor(float r, float g, float b)
{
	color = vec3(r, g, b);
}
