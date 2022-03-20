#include "Tool.h"
#include "Draw.h"

double Tool::Clamp(double value, double minimun, double maximun) {
	if (value > maximun) {
		return maximun;
	}
	if (value < minimun) {
		return minimun;
	}
	return value;
}

void  Tool::InitRand() {
	srand(time(0));
}

int  Tool::Rand(int a, int b) {
	return rand() % (b - a) + a;
}

SDL_Texture* Tool::openRescource(string imgPath) {
	if (!Draw::isInited) return NULL;

	return IMG_LoadTexture(Draw::ren, imgPath.c_str());
}