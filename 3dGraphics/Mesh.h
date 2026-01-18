#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Vector.h"
#include "Triange.h"

#define NUM_CUBE_VERTICIES 8

extern vec3_t cubeVerticies[NUM_CUBE_VERTICIES];

#define NUM_CUBE_FACES (6*2)
extern face_t cubeFaces[NUM_CUBE_FACES];

typedef struct {
	vec3_t* vertices;
	face_t* faces;
	vec3_t rotation;
} mesh_t;

extern mesh_t mesh;
void LoadCubeMeshData(void);
void loadObjDataFile(char* fileName);


