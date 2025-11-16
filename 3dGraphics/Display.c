#include "Display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* colourBufferTexture = NULL;
uint32_t* colourBuffer = NULL;
int windowWidth = 800;
int windowHeight = 600;

bool initialise_window(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error Initialising SDL.\n");
		return false;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	windowWidth = displayMode.w;
	windowHeight = displayMode.h;

	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);

	if (!window)
	{
		fprintf(stderr, "Error Initialising Window.\n");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error Initialising renderer.\n");
		return false;
	}

	colourBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
	if (!colourBufferTexture)
	{
		fprintf(stderr, "Error Initialising texture.\n");
		return false;
	}

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	return true;
}

void drawPixel(int x, int y, uint32_t colour)
{
	if (x >= 0 && x < windowWidth && y >= 0 && y < windowHeight)
	{
		colourBuffer[(windowWidth * y) + x] = colour;
	}
}


void drawRectangle(int xPos, int yPos, int width, int height, uint32_t colour)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int currentX = x + xPos;
			int currentY = y + yPos;
			drawPixel(currentX, currentY, colour);
		}
	}
}

void drawGrid()
{
	for (int y = 0; y < windowHeight; y += 10)
	{
		for (int x = 0; x < windowWidth; x += 10)
		{

			colourBuffer[(windowWidth * y) + x] = 0xFFFFFFFF;

		}
	}
}

void clearColourBuffer(uint32_t colour)
{
	for (int y = 0; y < windowHeight; y++)
	{
		for (int x = 0; x < windowWidth; x++)
		{
			colourBuffer[(windowWidth * y) + x] = colour;
		}
	}
}

void renderColourBuffer() {
	SDL_UpdateTexture(colourBufferTexture, NULL, colourBuffer, (int)windowWidth * sizeof(uint32_t));
	SDL_RenderCopy(renderer, colourBufferTexture, NULL, NULL);
}

void destroyWindow(void)
{
	free(colourBuffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


