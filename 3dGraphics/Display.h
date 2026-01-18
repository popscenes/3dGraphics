#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

#define FPS 30
#define FRAME_TARGET_TIME (1000/FPS)

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* colourBufferTexture;
extern uint32_t* colourBuffer;
extern int windowWidth;
extern int windowHeight;

bool initialise_window(void);
void drawRectangle(int xPos, int yPos, int width, int height, uint32_t colour);
void drawPixel(int x, int y, uint32_t colour);
void drawLine(int x0, int y0, int x1, int y1, uint32_t colour);
void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t colour);
void drawGrid();
void clearColourBuffer(uint32_t colour);
void renderColourBuffer();
void destroyWindow(void);