// (c) Marco Gilardi, 2017
#include "Transform.h"
#include <iostream>
using namespace std;

// The assumption for this class is that we are not attaching the game object to any hierachy so the coordinates are always expressed directly in world coordinates
Transform::Transform()
{
	// The first column of the transformation matrix matches the direction of the local x axis of the object expressed with respect to the world reference system in homogeneous coords
	// The second column of the transformation matrix matches the direction of the local y axis of the object expressed with respect to the world reference system in homogeneous coords
	// The third column of the transformation matrix contains the position of the object expressed with respect to the world reference system in homogeneous coords
	transformMatrix = mat3(1.0f, 0.0f, 0.0f,// 0.0f,
						   0.0f, 1.0f, 0.0f,// 0.0f,
						   0.0f, 0.0f, 1.0f);//, 0.0f,
						   //0.0f, 0.0f, 0.0f//, 1.0f //Identity matrix
													//inputs are done by column (i.e. the matrix is transposed)
}

// Translate the object by creating a Translation matrix and 
// multiplying it to the transform matrix
void Transform::Translate(const vec2 & translation)
{
	mat3 translationMatrix = mat3(		 1.0f,			0.0f,		0.0f, //0.0f,
										 0.0f,			1.0f,		0.0f, //0.0f,
										// 0.0f,			0.0f, 0.0f, //1.0f,
								translation.x,		 translation.y, 1.0f); //, translation.z
															// ^ This last Column is usually omitted in optimised code
															//	  because it is always constant (they use 2x3 matrices), 
															//    but as this code is didactic I left it here to help 
															//	  you match the code with the theory in the lectures

	transformMatrix = translationMatrix * transformMatrix;
}

// Scale the object by creating a Scaling matrix and 
// multiplying it to the transform matrix
void Transform::Scale(vec2& scaling)
{
	mat3 scalingMatrix = mat3(scaling.x, 0.0f,      0.0f,										//0.0f,
							  0.0f,      scaling.y, 0.0f,										// 0.0f,
							 // 0.0f,      0.0f,      0.0f,										//scaling.z, 
							  0.0f,      0.0f,      1.0f); //<-- Row omitted in optimised code  //, 1.0f

	transformMatrix = scalingMatrix * transformMatrix;
}
/*
// Rotate the object around its X local axis by creating a Rotation matrix and 
// multiplying it to the transform matrix
void Transform::RotateX(float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	mat4 rotateMatrix = mat4(1.0f,	0.0f,	0.0f,	0.0f,
							 0.0f,	   c,	   s,	0.0f,
							 0.0f,	  -s,	   c,	0.0f, 
							 0.0f,	0.0f,   0.0f,   1.0f); //<-- Row omitted in Optimised code

	transformMatrix = rotateMatrix * transformMatrix;
}

// Rotate the object around its Y local axis by creating a Rotation matrix and 
// multiplying it to the transform matrix
void Transform::RotateY(float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	mat4 rotateMatrix = mat4(	c,	0.0f,	   s,	0.0f, 
							 0.0f,	1.0f,	0.0f,	0.0f,
							   -s,	0.0f,	   c,	0.0f, 
							 0.0f,	0.0f,	0.0f,	1.0f); //<-- Row omitted in Optimised code

	transformMatrix = rotateMatrix * transformMatrix;
}
*/
// Rotate the object around its Z local axis by creating a Rotation matrix and 
// multiplying it to the transform matrix
void Transform::Rotate(float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	mat3 rotateMatrix = mat3(	c,	   s,	0.0f,	//0.0f,
							   -s,	   c,	0.0f,	//0.0f,
							 //0.0f,	0.0f,	1.0f,	0.0f,
							 0.0f,	0.0f,	0.0f); //<-- Row omitted in Optimised code ,	1.0f

	transformMatrix = rotateMatrix * transformMatrix;
}


vec2 Transform::getPosition() const
{
	vec3 col2 = column(transformMatrix, 2);
	return vec2(col2.x, col2.y); // The third column of the transformation matrix contains the position of the object in homogeneous coords //, col3.z
}

vec2 Transform::getScale() const
{
	float sx = length(column(transformMatrix, 0)); // It measures the length of the local x axis
	float sy = length(column(transformMatrix, 1)); // It measures the length of the local y axis
	//float sz = length(column(transformMatrix, 2)); // It measures the length of the local y axis
	return vec2(sx, sy);//, sz
}

vec2 Transform::getOrientation() const
{

	vec3 col0 = normalize(column(transformMatrix, 0)); // By normalising the x axis whe get the cosine (in the first component of the vector)
												       // and sine (in the second component of the vector) of the angle by which the object is rotated
	return vec2(col0.x, col0.y);
}

// This gives the y axis of the object expressed in world coordinates
vec2 Transform::getUpDir() const
{
	vec3 col1 = column(transformMatrix, 1);
	return vec2(col1.x, col1.y); // y Axis
}

// This gives the x axis of the object expressed in world coordinates
vec2 Transform::getLeftDir() const
{
	vec3 col0 = column(transformMatrix, 0);
	return vec2(col0.x, col0.y); // x Axis
}
/*
vec3 Transform::getFrontDir() const
{
	vec4 col2 = column(transformMatrix, 2);
	return vec3(col2.x, col2.y, col2.z); // z Axis
}*/

mat3 Transform::worldToLocalMatrix()
{
	return transformMatrix; //This matrix transforms world coordinates into local coordinates (if we are not using any hierarchical data structure)
}

mat3 Transform::localToWorldMatrix()
{
	return inverse(transformMatrix); 
}