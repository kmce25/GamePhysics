#pragma once
#include "Contact.h"
struct CollisionData
{
	Contact* contact = nullptr;
	int maxNumContacts;
	int numContactsLeft;

	virtual ~CollisionData() 
	{
		if(contact != nullptr) delete[] contact;
 	}
};