#pragma once
#include "PhysicsParameters.h"
#include "Solver.h"

class VerletSolver : public Solver
{
private:
	void solver(PhysicsParameters *Parameters, float dt);
public:

};