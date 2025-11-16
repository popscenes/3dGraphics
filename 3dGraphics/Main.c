#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include "Display.h"
#include "Vector.h"




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

	//for (int i = 0; i < N_POINTS; i++)
	//{
	//	vec3_t point = cubePoints[i];

	//	vec3_t transformedPoint = vec3RotateX(point, cubeRotation.x);
	//	transformedPoint = vec3RotateY(transformedPoint, cubeRotation.y);
	//	transformedPoint = vec3RotateZ(transformedPoint, cubeRotation.z);
	//	
	//	
	//	transformedPoint.z -= camer_position.z;
	//	vec2_t projectedPoint =  project(transformedPoint);
	//	

	//	projectedPoints[i] = projectedPoint;
	//}
}

void render(void)
{
	
	//for (int i = 0; i < N_POINTS; i++)
	//{
	//	vec2_t point = projectedPoints[i];
	//	drawRectangle(point.x + (windowWidth/2), point.y + (windowHeight/2), 4, 4, 0xFFFFFF00);
	//}
	
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