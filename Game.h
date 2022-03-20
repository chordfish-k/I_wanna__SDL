#pragma once

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <SDL.h>
#include <thread>
#include "Scene.h"

#include "Timer.h"
#include "Player.h"

using namespace std;


class Game {
public:
	static Game* game;
private:
	map<string, Scene* > scenes;
	enum class State {
		Loading,
		Running,
		Pausing,
		Ending
	}gameState;
	thread gameThread;
	thread uiThread;
	
public:	
	Scene* currentScene = NULL;
	SDL_Event eve = {};
	const int SCREEN_FPS = 50;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
	//每秒钟定时器的帧数
	LTimer fpsTimer;
	//每秒帧数上限定时器
	LTimer capTimer;
	int frameTicks = 0;
	bool keys[256] = {};
	bool keysJust[256] = {};

	

private:
	//void checkInteract();
	int delay;
	double dt;
	Player* player = NULL;
	bool waitToChangeScene = false;

	Scene* nextScene = NULL;//用于切换场景
	Vec2 nextPlayerPosition = { 0, 0 };

	Vec2 recordPlayerPos = { 0, 0 };//用于记录点
	string recordPlayerScene = "";

public:
	Game();
	void init(string windowName, int w, int h);
	void addScene(string name, Scene* s);
	void enterScene(string name, Vec2 playerPosition = {0, 0});
	void setPlayerRespawnPoint(string sceneName, Vec2 point);
	void returnPlayerRespawnPoint();
	Scene* getSceneByName(string sceneName) { return scenes[sceneName]; }
	State getGameState() { return gameState; };
	void start();
	void pause();
	void quit();
	void setDelay(int d) { delay = d; };
	void setDeltaTime(double dtt) { dt = dtt; };
	void setPlayer(Player* p) { player = p; };
	Player* getPlayer() { return player; };
};


#endif