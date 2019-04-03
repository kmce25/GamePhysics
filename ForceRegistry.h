#pragma once
#include "PhysicsParameters.h"
#include "PhysicsEntity.h"
#include "Force.h"
#include <vector>

using namespace std;
class ForceRegistry					//This class will register which forces are applied to which object and apply the resultant of forces to the object
{
private:
	struct ForceRegistration
	{
		PhysicsParameters* Parameters;
		Force* force;
	};
	vector<ForceRegistration> registrations;

public:

	virtual ~ForceRegistry(){}

	void Add(PhysicsEntity* obj, Force* ForceType);
	void Remove(PhysicsEntity* obj, Force* ForceType);
	void Clear();
	void updateForces(float dt);
};