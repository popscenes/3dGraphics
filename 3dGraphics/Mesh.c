#include "mesh.h"

vec3_t meshVerticies[NUM_MESH_VERTICIES] = {
	{.x = -1, .y = -1, .z = -1},
	{.x = -1, .y = 1, .z = -1},
	{.x = 1, .y = 1, .z = -1},
	{.x = 1, .y = -1, .z = -1},
	{.x = 1, .y = 1, .z = 1},
	{.x = 1, .y = -1, .z = 1},
	{.x = -1, .y = 1, .z = 1},
	{.x = -1, .y = -1, .z = 1},
};

#define NUM_MESH_FACES (6*2)
face_t meshFaces[NUM_MESH_FACES] = {
	{.a = 1, .b = 2, .c = 3},
	{.a = 1, .b = 3, .c = 4},

	{.a = 4, .b = 3, .c = 5},
	{.a = 4, .b = 5, .c = 6},

	{.a = 6, .b = 5, .c = 7},
	{.a = 6, .b = 7, .c = 8},

	{.a = 8, .b = 7, .c = 2},
	{.a = 8, .b = 2, .c = 1},

	{.a = 2, .b = 7, .c = 5},
	{.a = 2, .b = 5, .c = 3},

	{.a = 6, .b = 8, .c = 1},
	{.a = 6, .b = 1, .c = 4},
};