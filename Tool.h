#pragma once
#ifndef _TOOL_H_
#define _TOOL_H_

#include <iostream>
#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

class Tool {
public:

	static double Clamp(double value, double minimun, double maximun);

	static void InitRand();

	static int Rand(int a, int b);

	static SDL_Texture* openRescource(string imgPath);

};


#endif
