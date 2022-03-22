#include "Tool.h"
#include "Draw.h"
#include <SDL.h>

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
	//if (!Draw::isInited)return NULL;
		//IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
	//return IMG_LoadTexture(Draw::ren, imgPath.c_str());
	SDL_Surface *tmp = SDL_LoadBMP(imgPath.c_str());
	if (tmp == NULL) {
		return NULL;
	}
	Uint32 key = SDL_MapRGB(tmp->format, 255, 0,255);
	SDL_SetColorKey(tmp, 1, key);
	SDL_Texture *t= SDL_CreateTextureFromSurface(Draw::ren, tmp);
	SDL_FreeSurface(tmp);
	return t;
}