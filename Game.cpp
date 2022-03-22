#include "Game.h"
#include "Input.h"
#include "Draw.h"

Game* Game::game = NULL;

Game::Game() {
	if (!game) {
		game = this;
	}
	game->currentScene = NULL;
	game->eve = {};
	game->delay = 0;
	game->gameState = State::Loading;
	game->dt = 0;


}


void Game::init(string windowName, int w, int h) {
	//game = new Game();
	game->gameState = State::Loading;

	Draw::initDraw(windowName, w, h);
	Tool::InitRand();

}
void Game::addScene(string name, Scene* s) {
	if (game->scenes[name] != NULL) {
		delete game->scenes[name];
	}
	game->scenes[name] = s;
	//s->game = this;
}

void Game::enterScene(string name, Vec2 playerPosition ) {
	nextScene = game->scenes[name];
	//cout << name << " : " << (nextScene == NULL) << endl;
	waitToChangeScene = true;
	nextPlayerPosition = playerPosition;
}


void Game::start() {
	//if (!game->currentScene) return;

	game->gameState = State::Running;

	SDL_Event event = {};
	bool SHIFT_DOWN = false;

	int countedFrames = 0;
	game->fpsTimer.start();

	while (game->gameState != State::Ending) {



		game->capTimer.start();

		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			//avgFPS = 0;
		}
		++countedFrames;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				game->gameState = State::Ending;
				break;
			}
		}

		for (int i = 'A'; i <= 'Z'; i++) {
			game->keysJust[i] = (!game->keys[i] && Input::isKeyPress(i)) ? true : false;
			game->keys[i] = Input::isKeyPress(i);
			
		}
		game->keysJust[VK_SPACE] = (!game->keys[VK_SPACE] && Input::isKeyPress(VK_SPACE)) ? true : false;
		game->keys[VK_SPACE] = Input::isKeyPress(VK_SPACE);


		//检测reset
		if (game->keysJust['R']) {
			game->currentScene->reset();
			game->returnPlayerRespawnPoint();
			
		}
		

		if (game->currentScene)
			game->currentScene->onUpdate(SCREEN_TICKS_PER_FRAME / 1500.0);

		//cout << game->capTimer.getTicks() << " "<< game->frameTicks << endl;
		//如果帧提前完成
		game->frameTicks = game->capTimer.getTicks();
		//showFPS(avgFPS);
		if (game->frameTicks < game->SCREEN_TICKS_PER_FRAME)
		{
			//等待剩余时间
			//cout << SCREEN_TICKS_PER_FRAME - frameTicks << endl;
			SDL_Delay(game->SCREEN_TICKS_PER_FRAME - game->frameTicks);
		}


		if (waitToChangeScene) {
			waitToChangeScene = false;
			if (game->currentScene != NULL)
				game->currentScene->onExit();
			game->currentScene = game->nextScene;
			game->currentScene->onLoad(nextPlayerPosition);

		}
	}

}

void Game::pause() {
	game->gameState = State::Pausing;
}

void Game::quit() {
	game->gameState = State::Ending;
	for (auto i = game->scenes.begin(); i != game->scenes.end(); i++) {
		delete (i->second);
	}
}

void Game::setPlayerRespawnPoint(string sceneName, Vec2 point) {
	game->recordPlayerPos = point;
	game->recordPlayerScene = sceneName;
}

void Game::returnPlayerRespawnPoint() {
	enterScene(game->recordPlayerScene, game->recordPlayerPos);
}

