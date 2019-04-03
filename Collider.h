// (c) Marco Gilardi, 2017
#pragma once
#include <vector>
#include "glm\glm.hpp"
#include "Transform.h"
#include "Contact.h"

using namespace std;
using namespace glm;

class Collider
{
public:
	virtual const vec2 getCenter() const = 0;
	virtual void update(const Transform& transform) = 0;
};
