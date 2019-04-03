#pragma once
class Entity
{
public:
	virtual void update(float dt) = 0;
	virtual void Draw(int width, int height) = 0;
};