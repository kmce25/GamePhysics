#include "ContactResolver.h"

void ContactResolver::setNumIterations(int numIterations)
{
	ContactResolver::numIterations = numIterations;
}

void ContactResolver::resolveContacts(Contact * contactArray, int numContacts, float dt)
{

	iteration = 0;
	int maxIndex = numContacts;
	while (iteration < numIterations) {
		float max = 0;
		int maxIndex = numContacts;
		for (int i = 0; i < numContacts; i++) {
			float sepVel = contactArray[i].ComputeSeparatingVelocity();
			if (sepVel < max) {
				max = sepVel;
				maxIndex = i;
			}
		}
		if (maxIndex < numContacts)
		contactArray[maxIndex].Resolve(dt);
		iteration++;
	}
}
