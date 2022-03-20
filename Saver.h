#pragma once

#ifndef SAVER_H
#define SAVER_H

#include "Sprite.h"


class Saver : public Sprite {
private:
	SDL_Texture* before = NULL;
	SDL_Texture* after = NULL;
	string saveSceneName = "";
	Vec2 savePosition = {0,0};
	bool isSet = false;
	Animation* ani = NULL;
public:
	Saver(string sceneName, Vec2 pos);
	//Saver(Saver &s);
	void saverPoint();
	//Sprite* clone();
};

#endif