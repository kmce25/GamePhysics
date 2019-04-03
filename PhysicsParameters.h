#pragma once
#include <glm\glm.hpp>
#include "Transform.h"

struct PhysicsParameters		//Data structure to pass data, position, velocity, acceleration etc
{
private:
	float InverseMass;
	float Restitution;			//The bounce of an object 
	vec2 ForceAccum;

public:
	Transform transform;
	vec2 Velocity;
	vec2 Acceleration;
	vec2 GetResultantForce();

	void ClearAccumulator();
	void AddForce(const vec2& force);
	void SetInverseMass(float mass);
	void SetRestitution(float restit);

	float GetInverseMass();
	float GetMass();
	float GetRestitution();

	PhysicsParameters(float mass, vec2 pos, vec2 vel, float restit = 0)												//Constructor
		: Velocity(vel), Restitution(restit), ForceAccum(vec2(0)), Acceleration(vec2(0)), InverseMass(INFINITY)		//Initaliser 
	{
		SetInverseMass(mass);
		transform.Translate(pos);
	}

	virtual ~PhysicsParameters() {}																					//Deconstructor
};