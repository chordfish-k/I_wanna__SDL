#pragma once

#include <vector>
#include "Grid.h"
#include "Sprite.h"
#include "Player.h"
#include "Spike.h"
#include "Game.h"
#include "IWannaPalette.h"

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

	IWannaPalette* iwp;

	bool trap1 = false;

	double gameDt = 0;

	Vec2 playerGridPos;

public:
	GameScene_2() {
		gridH = 12;
		gridW = 15;

		grid = new Grid(gridH, gridW, 32, 32, 1);

		iwp = new IWannaPalette();
		grid->setPalette(iwp);
		/*sp1 = new Sprite(Vec2(0, 0), "res/block/floor_1.bmp");
		sp2 = new Sprite(Vec2(0, 0), "res/block/floor_2.bmp");

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
		grid->addNewTile("spike", spkleft);*/

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


		initTileTraps();

		
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
		resetTileTraps();

		player = Game::game->getPlayer();
		addChild("player", player);
		player->setPosition(playerPosition);

		player->setPosition(playerPosition);

		player->reset();
		grid->resetPositions();
	}

	void onExit() {

	}

	void resetTileTraps() {
		//Trap1
		grid->getTileAt(7, 7)->setData("trigerred", 0);

	}


	void initTileTraps() {

		grid->getTileAt(7, 7)
			->setUpdateFuncion([&](Sprite* self) {
			if (!self->getData("trigerred")) {
				if(playerGridPos.x == 7 && fabs(playerGridPos.y - 7) == 1)
					self->setData("trigerred", 1);
			}
			else {
				grid->tileMoveTo({ 7, 7 }, { 4, 7 }, 800 * gameDt);
			}
		});
	}

	void onUpdate(double dt) {
		Scene::onUpdate(dt);

		gameDt = dt;

		playerGridPos = grid->pointInGridXY(player->getPosition());

		if (playerGridPos.y == gridH) {
			Game::game->enterScene("scene1", Vec2(player->getPosition().x, player->getPosition().y - (grid->getTileH() ) * 1 * gridH));
		}

	}
};