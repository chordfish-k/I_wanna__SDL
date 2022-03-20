#pragma once

#include <vector>
#include "Grid.h"
#include "Sprite.h"
#include "Player.h"
#include "Spike.h"
#include "Game.h"

using namespace std;

class GameScene_2 : public Scene {
private:
	vector<Sprite*> sps;
	Grid* grid = NULL;
	int gridH;
	int gridW;

	Sprite* sp1 = NULL;
	Sprite* sp2 = NULL;

	Spike* spkup = NULL;
	Spike* spkright = NULL;
	Spike* spkdown = NULL;
	Spike* spkleft = NULL;

	Saver* saver = NULL;

	Player* player = NULL;

	bool trap1 = false;

public:
	GameScene_2() {
		gridH = 12;
		gridW = 15;

		grid = new Grid(gridH, gridW, 32, 32, 1);
		sp1 = new Sprite(Vec2(0, 0), "res/block/floor_1.png");
		sp2 = new Sprite(Vec2(0, 0), "res/block/floor_2.png");

		spkup = new Spike(0);
		spkright = new Spike(1);
		spkdown = new Spike(2);
		spkleft = new Spike(3);


		sp1->enableCollider = true;
		sp2->enableCollider = true;

		spkup->enableCollider = true;
		spkright->enableCollider = true;
		spkdown->enableCollider = true;
		spkleft->enableCollider = true;



		grid->addNewTile("floor", sp1);
		grid->addNewTile("floor", sp2);
		grid->addNewTile("spike", spkup);
		grid->addNewTile("spike", spkright);
		grid->addNewTile("spike", spkdown);
		grid->addNewTile("spike", spkleft);

		saver = new Saver("scene2", { 120, 45 });
		saver->setPosition({ 80, 50 });
		addChild("saver", saver);


		grid->setTiles({
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 2,
				2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2
			}, gridH, gridW);

		addChild("grid", grid);

		//player = new Player();
		//player->drawCollider = true;
		//player->setScale(0.7);
		//addChild("player", player);
		
	}

	~GameScene_2() {
		delete grid, sp1, sp2, spkup, spkright;
		grid = NULL;  sp1 = sp2 = spkup = spkright = NULL;
	}

	void onLoad() {
		//onLoad({ 50, (double)(Draw::H - 60) });
		//onLoad( { 140, (double)(Draw::H - 200) });
	}


	void onLoad(Vec2 playerPosition) {

		trap1 = false;

		player = Game::game->getPlayer();
		addChild("player", player);
		player->setPosition(playerPosition);

		player->reset();
		grid->resetPositions();
	}

	void onExit() {

	}

	void onUpdate(double dt) {
		Scene::onUpdate(dt);

		Vec2 playerGridPos = grid->pointInGridXY(player->getPosition());

		if (playerGridPos.y == gridH) {
			Game::game->enterScene("scene1", Vec2(player->getPosition().x, player->getPosition().y - (grid->getTileH() ) * 1 * gridH));
		}


		Vec2 trapPos(7, 7);

		if (!trap1 && playerGridPos.x == trapPos.x && fabs(playerGridPos.y - trapPos.y) == 1) {
			trap1 = true;
			
		}

		if (trap1) {
			grid->tileMoveTo(trapPos, {trapPos.x -3, trapPos.y}, 800*dt);
		}
	}
};