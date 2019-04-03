#pragma once
#include "glm\glm.hpp"
#include "Contact.h"

class ContactResolver {
private:
	int numIterations;
	int iteration;
public:
	ContactResolver() :numIterations(0) {}

	void setNumIterations(int numIterations);
	void resolveContacts(Contact* contactArray, int numContacts, float dt);
	virtual ~ContactResolver() {}
};