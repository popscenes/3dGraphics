#pragma once

typedef struct {
	float x;
	float y;
} vec2_t;

typedef struct {
	float x;
	float y;
	float z;
} vec3_t;

float Vect2length(vec2_t v);
vec2_t Vect2Add(vec2_t a, vec2_t b);
vec2_t Vect2Subtract(vec2_t a, vec2_t b);
vec2_t Vec2Multiply(vec2_t v, float factor);
vec2_t Vec2Divide(vec2_t v, float factor);
void Vec2Normalize(vec2_t* v);

float Vect3length(vec3_t v);
vec3_t Vect3Add(vec3_t a, vec3_t b);
vec3_t Vect3Subtract(vec3_t a, vec3_t b);
vec3_t Vec3Multiply(vec3_t v, float factor);
vec3_t Vec3Divide(vec3_t v, float factor);
vec3_t Vec3Cross(vec3_t a, vec3_t b);
float Vec3dot(vec3_t a, vec3_t b);
void Vec3Normalize(vec3_t* v);

vec3_t vec3RotateX(vec3_t v, float angle);
vec3_t vec3RotateY(vec3_t v, float angle);
vec3_t vec3RotateZ(vec3_t v, float angle);

