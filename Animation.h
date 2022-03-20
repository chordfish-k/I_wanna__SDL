#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>

using namespace std;

class Animation {
private:
	bool isEnd = false;
	int clipNum = 0;
	int currentClip = 0;
	double deltaFrame = 0.0;
	int framCounter = 0;
	vector<SDL_Texture*> clips;
	string name;
	
public:
	bool loop = false;
public:
	Animation(double deltaFrame);
	~Animation();
	Animation* add(string path);
	void next();
	bool checkEnd();
	Animation* setLoop(bool isLoop);
	Animation* setCurrentFrame(int index);
	SDL_Texture* getCurrentClip();

};

#endif