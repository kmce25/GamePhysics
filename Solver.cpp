#include "Solver.h"

using namespace std;

void Solver::Integrate(vector<PhysicsEntity*>& dynObjs, float dt)
{
	for (vector<PhysicsEntity*>::iterator it = dynObjs.begin();
										  it < dynObjs.end();
										  it++)
	{
		solver((*it)->GetParameters(), dt);
	}
								

}
