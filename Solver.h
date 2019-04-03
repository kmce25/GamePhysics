#pragma once
#include "PhysicsParameters.h"
#include "PhysicsEntity.h"
#include <vector>

using namespace std;

class Solver
{
private:
	virtual void solver(PhysicsParameters* Parameters, float dt) = 0;
public:
	void Integrate(vector<PhysicsEntity*>& dynObjs, float dt);
};