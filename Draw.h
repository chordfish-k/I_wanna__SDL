#pragma once
#ifndef _DRAW_H_
#define _DRAW_H_
#include <windows.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include "Vec2.h"
#include "Line.h"
#include "Color.h"


using namespace std;

class Draw {
public:

	static SDL_Window* win;
	static SDL_Renderer* ren;
	static int W;
	static int H;
	static Vec2 ZERO;
	static Color stored_color;
	static Color background_color;
	static bool isInited;
	static HWND hwnd;

//--------------------
	

	static int initDraw(string caption, int w, int h);
	static void quitDraw();
	static void DrawLine(Line2D& line, Color& color);
	static void DrawLine(Line2D& line);
	static void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	static void SetColor(Color& c);
	static void StoreColor();
	static void FillScreen(int x, int y, int w, int h);
	static void CleanCanvas();
	static void RefreshCanvas();

//-----------------
	
};




#endif