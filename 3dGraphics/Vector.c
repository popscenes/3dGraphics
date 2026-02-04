#include <math.h>
#include "Vector.h"

float Vect2length(vec2_t v)
{
	return sqrt((v.x * v.x) + (v.y * v.y));
}

vec2_t Vect2Add(vec2_t a, vec2_t b)
{
	vec2_t result = {
		.x = a.x + b.x,
		.y = a.y + b.y,
	};

	return result;
}

vec2_t Vect2Subtract(vec2_t a, vec2_t b)
{
	vec2_t result = {
		.x = a.x - b.x,
		.y = a.y - b.y,
	};

	return result;
}

vec2_t Vec2Multiply(vec2_t v, float factor)
{
	vec2_t result = {
		.x = v.x * factor,
		.y = v.y * factor
	};

	return result;
}

vec2_t Vec2Divide(vec2_t v, float factor)
{
	vec2_t result = {
		.x = v.x / factor,
		.y = v.y / factor
	};

	return result;
}

void Vec2Normalize(vec2_t* v)
{
	float vectorLength = sqrt(v->x * v->x + v->y * v->y);
	v->x = v->x / vectorLength;
	v->y = v->y / vectorLength;
}


float Vect3length(vec3_t v)
{
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}


vec3_t Vect3Add(vec3_t a, vec3_t b)
{
	vec3_t result = {
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z =a.z + b.z
	};

	return result;
}

vec3_t Vect3Subtract(vec3_t a, vec3_t b)
{
	vec3_t result = {
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	};

	return result;
}

vec3_t Vec3Multiply(vec3_t v, float factor)
{
	vec3_t result = {
		.x = v.x * factor,
		.y = v.y * factor,
		.z = v.z * factor
	};

	return result;
}

vec3_t Vec3Divide(vec3_t v, float factor)
{
	vec3_t result = {
		.x = v.x / factor,
		.y = v.y / factor,
		.z = v.z / factor
	};

	return result;
}

vec3_t Vec3Cross(vec3_t a, vec3_t b)
{
	vec3_t result = {
		.x = (a.y * b.z) - (a.z * b.y),
		.y = (a.z * b.x) - (a.x * b.z),
		.z = (a.x * b.y) - (a.y * b.x),
	};

	return result;
}

float Vec3dot(vec3_t a, vec3_t b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

void Vec3Normalize(vec3_t* v)
{
	float length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= length;
	v->y /= length;
	v->z /= length;
}





vec3_t vec3RotateX(vec3_t v, float angle)
{
	vec3_t rotatedVector = {
		.x = v.x,
		.y = v.y * cos(angle) - v.z * sin(angle),
		.z = v.y * sin(angle) + v.z * cos(angle)
	};

	return rotatedVector;
}

vec3_t vec3RotateY(vec3_t v, float angle)
{
	vec3_t rotatedVector = {
		.x = v.x * cos(angle) - v.z * sin(angle),
		.y = v.y,
		.z = v.x * sin(angle) + v.z * cos(angle)
	};

	return rotatedVector;
}

vec3_t vec3RotateZ(vec3_t v, float angle)
{
	vec3_t rotatedVector = {
		.x = v.x * cos(angle) - v.y * sin(angle),
		.y = v.x * sin(angle) + v.y * cos(angle),
		.z = v.z
	};

	return rotatedVector;
}