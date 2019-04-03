//updates at half time intervals rather than updating at each time interval
#include "VerletSolver.h"

void VerletSolver::solver(PhysicsParameters * Parameters, float dt)
{
	Parameters->transform.Translate(dt * Parameters->Velocity + 0.5f * dt * dt * Parameters->Acceleration);			//Full time step
	Parameters->Velocity += 0.5f * dt * Parameters->Acceleration;													//Half time step
	Parameters->Acceleration = Parameters->GetResultantForce() * Parameters->GetInverseMass();						// a = f/m (m == inverse mass ~ divide)
	Parameters->Velocity += 0.5f * dt * Parameters->Acceleration;
}
