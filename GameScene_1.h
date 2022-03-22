#pragma once

#include <iostream>
#include <vector>
#include "Grid.h"
#include "Sprite.h"
#include "Player.h"
#include "Spike.h"
#include "Saver.h"
#include "IWannaPalette.h"

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

	IWannaPalette *iwp;

	double gameDt = 0;

	Vec2 playerGridPos;
	Vec2 playerRecordpoint;

public:
	GameScene_1() {
		gridH = 12;
		gridW = 15;

		grid = new Grid(gridH, gridW, 32, 32, 1);

		iwp = new IWannaPalette();
		grid->setPalette(iwp);


		saver = new Saver("scene1", { 120, 200 });
		iwp->add("saver", saver);
		//addChild("saver", saver);

		grid->setTiles({
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 3, 0, 0, 7, 0, 0, 0, 3, 3, 0, 0, 0, 0, 2,
				2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 3, 2,
				2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
		}, gridH, gridW);

		addChild("grid", grid);

		initTileTraps();
	}

	void onLoad() {
		
		onLoad({ 50, (double)(Draw::H - 60) });
		//onLoad({ 140, (double)(Draw::H - 200) });
	}


	void onLoad(Vec2 playerPosition) {
		playerRecordpoint = playerPosition;

		
		player = Game::game->getPlayer();
		addChild("player", player);
		
		player->setPosition(playerPosition);
		
		player->reset();
		exited = false;
	}		

	void reset() {
		player->setPosition(playerRecordpoint);
		playerGridPos = grid->pointInGridXY(playerRecordpoint);
		resetTileTraps();
		grid->resetPositions();
		
		
	}


	void resetTileTraps() {
		//Trap1
		grid->getTileAt(13, 10)->setData("trigerred", 0);

		//Trap2
		grid->getTileAt(8, 8)->setData("trigerred", 0);
		grid->getTileAt(5, 11)->setData("trigerred", 0);
		grid->getTileAt(4, 11)->setData("trigerred", 0);

		//Trap3
		grid->getTileAt(1, 6)->setData("trigerred", 0);
	}


	void initTileTraps() {
		//Trap1
		grid->getTileAt(13, 10)
			->setUpdateFuncion([&](Sprite* self) {
			//cout << self->getData("trigerred") << endl;
			if (!self->getData("trigerred")) {
				if (playerGridPos.x == 13) {
					self->setData("trigerred", 1);
					
				}
			}
			else {

				grid->tileMoveTo({ 13, 10 }, { 13, -15 }, 800 * gameDt);
			}
		});

		//Trap2
		grid->getTileAt(4, 11)
			->setCollidedFuncion([&](Sprite* self, Vec2 dir) {
			if (!self->getData("trigerred")) {
				
				self->setData("trigerred", 1);
			}
		});
		grid->getTileAt(4, 11)
			->setUpdateFuncion([&](Sprite* self) {
			if (self->getData("trigerred")) {

				grid->tileMoveTo({ 4, 11 }, { 6, 20 }, 600 * gameDt);
			}
		});
		grid->getTileAt(5, 11)
			->setCollidedFuncion([&](Sprite* self, Vec2 dir) {
			if (!self->getData("trigerred")) {

				self->setData("trigerred", 1);
			}
		});
		
		grid->getTileAt(5, 11)
			->setUpdateFuncion([&](Sprite* self) {
			if (self->getData("trigerred")) {

				grid->tileMoveTo({ 5, 11 }, { 5, 20 }, 600 * gameDt);
			}
		});

		grid->getTileAt(8, 8)
			->setUpdateFuncion([&](Sprite* self) {
			if (self->getData("trigerred") == 0) {

				grid->tileMoveTo({ 8, 8 }, { 8, 7 }, 600);
				self->setData("trigerred", 1);
			}
			else if(self->getData("trigerred") == 1) {
				if(playerGridPos.x == 8 && playerGridPos.y >= 8)
					self->setData("trigerred", 2);
			}
			else if (self->getData("trigerred") == 2) {
				grid->tileMoveTo({ 8, 8 }, { 8, 8 }, 600 * gameDt);
			}
		});
		//grid->getTileAt(7, 11)
		//	->setCollidedFuncion([&](Sprite* self, Vec2 dir) {
		//	if (!self->getData("trigerred")) {

		//		self->setData("trigerred", 1);
		//	}
		//});

		//grid->getTileAt(7, 11)
		//	->setUpdateFuncion([&](Sprite* self) {
		//	if (self->getData("trigerred")) {

		//		grid->tileMoveTo({ 7, 11 }, { 7, 20 }, 600 * gameDt);
		//	}
		//});

		//Trap3
		grid->getTileAt(1, 6)
			-> setUpdateFuncion([&](Sprite* self) {
			if (!self->getData("trigerred")) {
				if (playerGridPos.x == 2 && playerGridPos.y <= 4)
					self->setData("trigerred", 1);
			}
			else {
				Vec2 spikePos = grid->pointInGridXY(self->getPosition());
				
				

				if (self->getData("trigerred") == 1 && spikePos.y >= 3) {
					bool reach = grid->tileMoveTo({1, 6}, { 2, 3 }, 500 * gameDt);
					if (reach) self->setData("trigerred", 2);

					self->rotateTo(90, 10 * gameDt);
				}
				else if (self->getData("trigerred") == 2 && playerGridPos.x >= 7) {
					
					bool reach = grid->tileMoveTo({1, 6}, { 25, 3 }, 1000 * gameDt);
					if (reach) self->setData("trigerred", 3);
				}
				else if (self->getData("trigerred") == 3) {

					bool reach = grid->tileMoveTo({ 1, 6 }, { 1, 3 }, 1000 * gameDt);
					if (reach) self->setData("trigerred", 3);
					self->rotateTo(-90, 50 * gameDt);
				}
			}
		});

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

		delete iwp; iwp = NULL;
	}

	void onUpdate(double dt) {
		Scene::onUpdate(dt);
		if (exited) return;

		gameDt = dt;

		playerGridPos = grid->pointInGridXY(player->getPosition());

		//场景切换
		if (player->getPosition().y < 0) {
			Game::game->enterScene("scene2", Vec2(player->getPosition().x, player->getPosition().y + (grid->getTileH()) * 1 * (gridH-2)));
		}
		
		////Trap1
		//Vec2 trapTile1Pos = { 13, 10 };
		//Node* spkup_1 = grid->getTileAt(trapTile1Pos.y, trapTile1Pos.x);
		////if (fabs(spkup_1->getPosition().x - player->getPosition().x) < 10) {
		//if (!spikeTrap1 && playerGridPos.x == 13) {
		//	spikeTrap1 = true;
		//}


		//if (spikeTrap1) { //{ 0, -800 * dt }
		//	grid->tileMoveTo(trapTile1Pos, { trapTile1Pos.x, -1 }, 800 * dt);
		//}


		//Trap2
		//Vec2 trapTile2Pos = { 1, 6 };
		//Sprite* spkup_2 = grid->getTileAt(trapTile2Pos.x, trapTile2Pos.y);
		//if (!spikeTrap2 && playerGridPos.x == 2 && playerGridPos.y <= 4) {
		//	spikeTrap2 = true;
		//}

		//if (spikeTrap2) {
		//	Vec2 spikePos = grid->pointInGridXY(spkup_2->getPosition());
		//	
		//	if(playerGridPos.x >= 7) {
		//			grid->tileMoveTo(trapTile2Pos, { 16, 3 }, 1000 * dt);
		//		
		//	}
		//	
		//	else if (spikePos.y >= 3) {
		//		grid->tileMoveTo(trapTile2Pos, { 2, 3 }, 500 * dt);
		//		spkup_2->rotateTo(90, 10 * dt);
		//	}
		//}

		//处理场景机关逻辑 end
	}
};