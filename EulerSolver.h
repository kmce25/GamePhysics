#pragma once
#include "PhysicsParameters.h"
#include "Solver.h"

class EulerSolver : public Solver
{
private:
	void solver(PhysicsParameters *Parameters, float dt);
public:
};