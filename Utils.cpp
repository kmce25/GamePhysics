// (c) Marco Gilardi, 2017
#include <limits>
#include <iostream>

#include "Utils.h"
#include "AABB.h"
#include "BoundingSphere.h"

using namespace std;

//UP: vec3(0, 1, 0)
const vec2 Utils::up = vec2(0, 1);
//UP: vec3(0, -1, 0)
const vec2 Utils::down = vec2(0, -1);

//RIGHT: vec3(1, 0, 0)
const vec2 Utils::right = vec2(1, 0);
//LEFT: vec3(-1, 0, 0)
const vec2 Utils::left = vec2(-1, 0);

float Utils::distanceBetweenPoints(const vec2 & P, const vec2 & Q)
{
	return distance(P, Q);
}

float Utils::disanceBetweenPointAndPlane(const vec2 & P, const vec2 & n, float d)
{
	return abs(dot(P, n) - d);
}

bool Utils::pointIsAbovePlane(const vec2 & P, const vec2 & n, float d)
{
	return dot(n, P) + d > FLT_EPSILON;
}

vec2 Utils::projectPointOnAABB(const vec2 & P, const AABB* const aabb)
{
	vec2 center = aabb->getCenter();
	vec2 radii = aabb->getRadii();
	vec2 normal = Utils::getAABBFaceNormal(P, aabb);
	float d = abs(dot(normal, radii));
	vec2 point = projectPointOnPlane(P - center, normal, d);
	return point + center;
}

vec2 Utils::getAABBFaceNormal(const vec2& const P, const AABB* const aabb)
{
	char mask = Utils::computePointMask(P, aabb);
	vec2 normal = vec2(0);
	if ((mask & 1) == 1)	// +x
	{
		normal += Utils::right;
	}
	if ((mask & 2) == 2)	// -x
	{
		normal += Utils::left;
	}
	if ((mask & 4) == 4)	// +y
	{
		normal += Utils::up;
	}
	if ((mask & 8) == 8)	// -y
	{
		normal += Utils::down;
	}
	return normalize(normal);
}

vec2 Utils::projectPointOnPlane(const vec2& P, const vec2& n, float c)
{
	float d = Utils::disanceBetweenPointAndPlane(P, n, c);
	return P - d * n;
}

float Utils::clamp(float val)
{

	if (val < 0)
		return 0;
	else if (val>1)
		return 1;
	else
		return val;

	//return max(min(val, 1.0f), 0.0f); //alternative implementation
}

/*
Mask is computed as in the following ASCII image.

This is foe the 2D case with codes for +/-x and +/-y

0110	|	+y 0100   	|	0101
-----------------------------------
-x 0010	|	   0000		|	+x 0001
-----------------------------------
1010	|	-y 1000  	|	1001

the 3D case for +/-z is similar but using 6 bits instead of 4

*/
char Utils::computePointMask(const vec2& P, const AABB* aabb)
{
	vec2 center = aabb->getCenter();
	vec2 radii = aabb->getRadii();

	char mask = 0;
	if (pointIsAbovePlane(P, Utils::right, -center.x - radii.x))
	{
		//cout << "X" << endl;
		mask |= 1;// +x
	}
	if (pointIsAbovePlane(P, Utils::left, center.x - radii.x))
	{
		//cout << "-X" << endl;
		mask |= 2;	// -x
	}
	if (pointIsAbovePlane(P, Utils::up, -center.y - radii.y))
	{
		//cout << "Y" << endl;
		mask |= 4;	// +y
	}
	if (pointIsAbovePlane(P, Utils::down, center.y - radii.y))
	{
		//cout << "-Y" << endl;
		mask |= 8;	// -y
	}
	return mask;
}

