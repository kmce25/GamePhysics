#include "EulerSolver.h"

void EulerSolver::solver(PhysicsParameters * Parameters, float dt)
{
	Parameters->transform.Translate(dt * Parameters->Velocity);
	Parameters->Velocity += dt * Parameters->Acceleration;
	Parameters->Acceleration = Parameters->GetResultantForce() * Parameters->GetInverseMass();
}
