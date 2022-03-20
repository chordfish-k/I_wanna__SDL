#pragma once

#include <iostream>
#include <vector>
#include "Grid.h"
#include "Sprite.h"
#include "Player.h"
#include "Spike.h"
#include "Saver.h"

using namespace std;

class GameScene_1 : public Scene {
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
	
	Polygon2D* rect = NULL;

	bool spikeTrap1 = false;
	bool spikeTrap2 = false;
	bool spikeTrap3 = false;

	bool exited = false;


	
public:
	GameScene_1() {
		gridH = 12;
		gridW = 15;

		grid = new Grid(gridH, gridW, 32, 32, 1);
		sp1 = new Sprite(Vec2(0, 0), "res/block/floor_1.png");
		sp2 = new Sprite(Vec2(0, 0), "res/block/floor_2.png");

		spkup = new Spike(0);
		spkright = new Spike(1);
		spkdown = new Spike(2);
		spkleft = new Spike(3);

		

		//sp1->drawCollider = true;
		//sp2->drawCollider = true;
		//sp3->drawCollider = true;
		sp1->enableCollider = true;
		sp2->enableCollider = true;

		spkup->enableCollider = true;
		spkright->enableCollider = true;
		spkdown->enableCollider = true;
		spkleft->enableCollider = true;
		//spkup->drawCollider = true;
		

		grid->addNewTile("floor", sp1);
		grid->addNewTile("floor", sp2);
		grid->addNewTile("spike", spkup);
		grid->addNewTile("spike", spkright);
		grid->addNewTile("spike", spkdown);
		grid->addNewTile("spike", spkleft);

		saver = new Saver("scene1", { 50, 300 });
		saver->setPosition({50, 340});
		addChild("saver", saver);


		grid->setTiles({
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 3, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 2,
				2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 3, 2,
				2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
		}, gridH, gridW);

		addChild("grid", grid);

		
	}

	void onLoad() {
		
		onLoad({ 50, (double)(Draw::H - 60) });
		//onLoad({ 140, (double)(Draw::H - 200) });
	}


	void onLoad(Vec2 playerPosition) {
		exited = false;
		spikeTrap1 = false;
		spikeTrap2 = false;
		player = Game::game->getPlayer();
		addChild("player", player);

		player->setPosition(playerPosition);

		player->reset();
		//player->reset();
		grid->resetPositions();
	}			

	void reset() {
		
		
		
	}
		
	void onExit() {
		
		exited = true;
	}

	~GameScene_1() {
		cout << "xigou" << endl;
		delete grid, sp1, sp2, spkup, spkright;
		delete saver;
		grid = NULL; 
		sp1 = sp2 = spkup = spkright = NULL;
		saver = NULL;
	}

	void onUpdate(double dt) {
		Scene::onUpdate(dt);
		if (exited) return;

		Vec2 playerGridPos = grid->pointInGridXY(player->getPosition());

		//场景切换
		if (player->getPosition().y < 0) {
			Game::game->enterScene("scene2", Vec2(player->getPosition().x, player->getPosition().y + (grid->getTileH()) * 1 * (gridH-2)));
		}
		

		//处理场景机关逻辑 start

		
		//Trap1
		Vec2 trapTile1Pos = {13, 10};
		Node *spkup_1 = grid->getTileAt(trapTile1Pos.y, trapTile1Pos.x);
		//if (fabs(spkup_1->getPosition().x - player->getPosition().x) < 10) {
		if(!spikeTrap1 && playerGridPos.x == 13){
			spikeTrap1 = true;
		}


		if (spikeTrap1) { //{ 0, -800 * dt }
			grid->tileMoveTo(trapTile1Pos, {trapTile1Pos.x, -1}, 800 * dt);
		}

		//Trap2
		Vec2 trapTile2Pos = { 1, 6 };
		Sprite* spkup_2 = grid->getTileAt(trapTile2Pos.y, trapTile2Pos.x);
		if (!spikeTrap2 && playerGridPos.x == 2 && playerGridPos.y <= 4) {
			spikeTrap2 = true;
		}

		if (spikeTrap2) {
			Vec2 spikePos = grid->pointInGridXY(spkup_2->getPosition());
			
			if(playerGridPos.x >= 7) {
					grid->tileMoveTo(trapTile2Pos, { 16, 3 }, 1000 * dt);
				
			}
			
			else if (spikePos.y >= 3) {
				grid->tileMoveTo(trapTile2Pos, { 2, 3 }, 500 * dt);
				spkup_2->rotateTo(90, 10 * dt);
			}
		}

		//处理场景机关逻辑 end
	}
};