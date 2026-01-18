#include <stdio.h>
#include "mesh.h"
#include "Array.h"

mesh_t mesh = {
	.vertices = NULL,
	.faces = NULL,
	.rotation = {0,0,0}
};

vec3_t cubeVerticies[NUM_CUBE_VERTICIES] = {
	{.x = -1, .y = -1, .z = -1},
	{.x = -1, .y = 1, .z = -1},
	{.x = 1, .y = 1, .z = -1},
	{.x = 1, .y = -1, .z = -1},
	{.x = 1, .y = 1, .z = 1},
	{.x = 1, .y = -1, .z = 1},
	{.x = -1, .y = 1, .z = 1},
	{.x = -1, .y = -1, .z = 1},
};

#define NUM_CUBE_FACES (6*2)
face_t cubeFaces[NUM_CUBE_FACES] = {
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

void LoadCubeMeshData() {
	for (int i = 0; i < NUM_CUBE_VERTICIES; i++)
	{
		array_push(mesh.vertices, cubeVerticies[i]);
	}

	for (int i = 0; i < NUM_CUBE_FACES; i++)
	{
		array_push(mesh.faces, cubeFaces[i]);
	}
}

void loadObjDataFile(char* fileName)
{
    FILE* objFile;
    errno_t err = 0;
    char line[256];

    fopen_s(&objFile, fileName, "r");
    if (err != 0)
    {
        return;
    }

    while (fgets(line, sizeof(line), objFile))
    {
        if (line[0] == 'v' && line[1] == ' ')
        {
            char* next_token1 = NULL;
            char* token = strtok_s(line, " ", &next_token1);

            token = strtok_s(NULL, " ", &next_token1);
            float vecX = atof(token);

            token = strtok_s(NULL, " ", &next_token1);
            float vecY = atof(token);

            token = strtok_s(NULL, " ", &next_token1);
            float vecZ = atof(token);

            vec3_t cubeVertex = { vecX, vecY, vecZ };
            array_push(mesh.vertices, cubeVertex);

        }

        if (line[0] == 'f')
        {
            char* next_token1 = NULL;
            char* token = strtok_s(line, " ", &next_token1);

            token = strtok_s(NULL, " ", &next_token1);
            int faceA = atoi(&token[0]);

            token = strtok_s(NULL, " ", &next_token1);
            int faceB = atoi(&token[0]);

            token = strtok_s(NULL, " ", &next_token1);
            int faceC = atoi(&token[0]);

            face_t cubeFace = { faceA, faceB, faceC };
            array_push(mesh.faces, cubeFace);
        }

    }
}

