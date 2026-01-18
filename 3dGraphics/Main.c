#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include "Display.h"
#include "Vector.h"
#include "mesh.h"
#include "Array.h"

triangle_t* trianglesToRender = NULL;

float fovFactor = 640;
vec3_t camer_position = { 0,0,-5 };

bool is_running;

int previousFrameTime = 0;

void setup(void)
{
	loadObjDataFile("./assets/cube.obj");
	//LoadCubeMeshData();
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

	trianglesToRender = NULL;

	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
	{
		SDL_Delay(timeToWait);
	}
	previousFrameTime = SDL_GetTicks();
	
	mesh.rotation.x += 0.01;
	mesh.rotation.y += 0.01;
	mesh.rotation.z += 0.01;

	int numFaces = array_length(mesh.faces);
	for (int i = 0; i < numFaces; i++)
	{
		face_t meshFace = mesh.faces[i];

		vec3_t faceVerticies[3];

		faceVerticies[0] = mesh.vertices[meshFace.a-1];
		faceVerticies[1] = mesh.vertices[meshFace.b-1];
		faceVerticies[2] = mesh.vertices[meshFace.c-1];


		triangle_t projectedTriange;
		for (int j = 0; j < 3; j++)
		{
			vec3_t transformedVertex = faceVerticies[j];
			transformedVertex = vec3RotateX(transformedVertex, mesh.rotation.x);
			transformedVertex = vec3RotateY(transformedVertex, mesh.rotation.y);
			transformedVertex = vec3RotateZ(transformedVertex, mesh.rotation.z);

			transformedVertex.z -= camer_position.z;

			vec2_t projectedPoint = project(transformedVertex);

			projectedPoint.x += (windowWidth / 2);
			projectedPoint.y += (windowHeight / 2);

			projectedTriange.points[j] = projectedPoint;
		}
		
		array_push(trianglesToRender, projectedTriange);
	}
}

void render(void)
{
	
	int numTriangles = array_length(trianglesToRender);
	for (int i = 0; i < numTriangles; i++)
	{
		triangle_t triangleToRender = trianglesToRender[i];
		drawRectangle(triangleToRender.points[0].x, triangleToRender.points[0].y, 4, 4, 0xFFFFFF00);
		drawRectangle(triangleToRender.points[1].x, triangleToRender.points[1].y, 4, 4, 0xFFFFFF00);
		drawRectangle(triangleToRender.points[2].x, triangleToRender.points[2].y, 4, 4, 0xFFFFFF00);

		drawTriangle(
			triangleToRender.points[0].x, triangleToRender.points[0].y,
			triangleToRender.points[1].x, triangleToRender.points[1].y,
			triangleToRender.points[2].x, triangleToRender.points[2].y,
			0xFF00FF00
		);
	}

	array_free(trianglesToRender);
	renderColourBuffer();
	clearColourBuffer(0xFF000000);
	
	SDL_RenderPresent(renderer);
}

void freeResources()
{
	array_free(mesh.faces);
	array_free(mesh.vertices);
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
	freeResources();

	return 0;
}