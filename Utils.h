// (c) Marco Gilardi, 2017
#pragma once

#include <glm\glm.hpp>
using namespace glm;

class BoundingSphere;
class AABB;

class Utils
{
public:
	static const vec2 up;
	static const vec2 down;
	static const vec2 left;
	static const vec2 right;

	static float distanceBetweenPoints(const vec2& P, const vec2& Q);
	static float disanceBetweenPointAndPlane(const vec2& P, const vec2& n, float d);
	static char computePointMask(const vec2& P, const AABB* const aabb);
	static vec2 projectPointOnAABB(const vec2& P, const AABB* const aabb);
	static vec2 getAABBFaceNormal(const vec2 & P, const AABB * const aabb);
	static bool pointIsAbovePlane(const vec2& P, const vec2& n, float c);
	static vec2 projectPointOnPlane(const vec2& P, const vec2& n, float c);
	static float clamp(float val);

private:
	Utils() {}
};