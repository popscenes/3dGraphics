#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include "Display.h"
#include "Vector.h"
#include "mesh.h"

triangle_t trianglesToRender[NUM_MESH_FACES];

float fovFactor = 640;
vec3_t cubeRotation = { 0,0,0 };
vec3_t camer_position = { 0,0,-5 };

bool is_running;

int previousFrameTime = 0;

void setup(void)
{
	colourBuffer = (uint32_t*)malloc(sizeof(uint32_t) * windowWidth * windowHeight);
}

void processInput(void)
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{	
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				is_running = false;
			}
			break;
		default:
			break;
	}
}

vec2_t project(vec3_t point)
{
	vec2_t projectedPoint = {
		.x = (fovFactor * point.x) /point.z,
		.y = (fovFactor * point.y) /point.z
	};

	return projectedPoint;
}

void update(void)
{
	
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - previousFrameTime);

	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
	{
		SDL_Delay(timeToWait);
	}
	previousFrameTime = SDL_GetTicks();
	
	cubeRotation.x += 0.01;
	cubeRotation.y += 0.01;
	cubeRotation.z += 0.01;

	for (int i = 0; i < NUM_MESH_FACES; i++)
	{
		face_t meshFace = meshFaces[i];

		vec3_t faceVerticies[3];

		faceVerticies[0] = meshVerticies[meshFace.a-1];
		faceVerticies[1] = meshVerticies[meshFace.b-1];
		faceVerticies[2] = meshVerticies[meshFace.c-1];


		triangle_t projectedTriange;
		for (int j = 0; j < 3; j++)
		{
			vec3_t transformedVertex = faceVerticies[j];
			transformedVertex = vec3RotateX(transformedVertex, cubeRotation.x);
			transformedVertex = vec3RotateY(transformedVertex, cubeRotation.y);
			transformedVertex = vec3RotateZ(transformedVertex, cubeRotation.z);

			transformedVertex.z -= camer_position.z;

			vec2_t projectedPoint = project(transformedVertex);

			projectedPoint.x += (windowWidth / 2);
			projectedPoint.y += (windowHeight / 2);

			projectedTriange.points[j] = projectedPoint;
		}

		trianglesToRender[i] = projectedTriange;
		
	}
}

void render(void)
{
	
	for (int i = 0; i < NUM_MESH_FACES; i++)
	{
		triangle_t triangleToRender = trianglesToRender[i];
		drawRectangle(triangleToRender.points[0].x, triangleToRender.points[0].y, 4, 4, 0xFFFFFF00);
		drawRectangle(triangleToRender.points[1].x, triangleToRender.points[1].y, 4, 4, 0xFFFFFF00);
		drawRectangle(triangleToRender.points[2].x, triangleToRender.points[2].y, 4, 4, 0xFFFFFF00);
	}
	
	renderColourBuffer();
	clearColourBuffer(0xFF000000);
	
	SDL_RenderPresent(renderer);
}

int main(int argc, char* args[])
{
	is_running = initialise_window();

	setup();

	

	while (is_running)
	{
		processInput();
		update();
		render();
	}

	destroyWindow();

	return 0;
}