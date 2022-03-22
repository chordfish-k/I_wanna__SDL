#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "OverSDL.h"

#include "GameScene_1.h"
#include "GameScene_2.h"


const int WIDTH = 32 * 15;
const int HEIGHT = 32* 12;

using namespace std;


bool quit = false;

const int SCREEN_FPS = 50;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
//每秒钟定时器的帧数
LTimer fpsTimer;
//每秒帧数上限定时器
LTimer capTimer;
int frameTicks;

Player* player = NULL;

//--------

int main(int args, char* argv[]) {

	Game game;
	game.init("I Wanna do some Tests", WIDTH, HEIGHT);

	player = new Player();
	player->drawCollider = true;
	player->setScale(0.65);
	player->visable = true;
	

	
	//Scene* scene = new GameScene();
	
	Scene* scene1 = new GameScene_1();
	Scene* scene2 = new GameScene_2();

	game.addScene("scene1", scene1);
	game.addScene("scene2", scene2);

	game.setPlayer(player);

	Vec2 playerPos = { 50, 300 };
	//Vec2 playerPos = { 120, (double)(Draw::H - 200) };
	game.setPlayerRespawnPoint("scene1", playerPos);
	//game.setPlayerRespawnPoint("scene2", playerPos);

	game.enterScene("scene1", playerPos);
	//game.enterScene("scene2", playerPos);
	game.start();



	cout << "CANCEL" << endl;
	//SDL_Delay(2000);
	
	game.quit();

	return 0;
}



