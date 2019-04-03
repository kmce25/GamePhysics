#pragma once
#include "Force.h"
#include "PhysicsEntity.h"

class Drag : public Force
{
private:
	float k1;				//Linear value of drag?	
	float k2;				
public:
	Drag(float k1, float k2) :k1(k1), k2(k2) {}
	virtual ~Drag() {}
	void updateForce(PhysicsParameters* obj, float dt);
};
