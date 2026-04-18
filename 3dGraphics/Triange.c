#include "Triange.h"

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;

}

void fillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t colour)
{

	float invSlope1 = (float)(x1 - x0) / (y1 - y0);
	float invSlope2 = (float)(x2 - x0) / (y2 - y0);

	float xStart = x0;
	float xend = x0;

	for (int y = y0; y <= y2; y++)
	{
		drawLine(xStart, y, xend, y, colour);
		xStart += invSlope1;
		xend += invSlope2;
	}

}

void fillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t colour)
{
	float invSlope1 = (float)(x2 - x0) / (y2 - y0);
	float invSlope2 = (float)(x2 - x1) / (y2 - y1);

	float xStart = x2;
	float xend = x2;

	for (int y = y2; y >= y0; y--)
	{
		drawLine(xStart, y, xend, y, colour);
		xStart -= invSlope1;
		xend -= invSlope2;
	}
}

void drawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t colour)
{
	if (y0 > y1)
	{
		swap(&y0, &y1);
		swap(&x0, &x1);
	}


	if (y1 > y2)
	{
		swap(&y1, &y2);
		swap(&x1, &x2);
	}

	if (y0 > y1)
	{
		swap(&y0, &y1);
		swap(&x0, &x1);
	}

	if (y1 == y2)
	{
		fillFlatBottomTriangle(x0, y0, x1, y1, x2, y2, colour);
		return;
	}
	else if (y0 == y1)
	{
		fillFlatTopTriangle(x0, y0, x1, y1, x2, y2, colour);
		return;
	}

	int my = y1;
	int mx = ((float)((x2 - x0) * (y1 - y0)) / (float)(y2 - y0)) + x0;

	fillFlatBottomTriangle(x0, y0, x1, y1, mx, my, colour);
	fillFlatTopTriangle(x1, y1, mx, my, x2, y2, colour);
}
