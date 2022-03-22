#include "Vec2.h"
#include "Grid.h"
#include "Rectangle.h"
#include "Spike.h"
#include "Saver.h"
#include <sstream>

Grid::Grid(int H, int W, int tileH, int tileW, double scale)
	:H(H), W(W), tileH(tileH), tileW(tileW), scale(scale) {
	tileTypeNums = 0;
	resetSize(H, W);
	//0空气
	//spriteMap[0] = new Sprite();
	anchor = Vec2(0.5, 0.5);
}

void Grid::resetSize(int H, int W) {
	for (int i = 0; i < H * W; i++) {
		grid.push_back(0);
		spriteGrid.push_back(NULL);
	}
}

vector<Node*> Grid::getAllChildren() {
	vector<Node*> res;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (grid[i * W + j])
				res.push_back(spriteGrid[i * W + j]);
		}
	}
	return res;
}

void Grid::setTileSprite(int i, int j, int id) {
	if (spriteGrid[i * W + j] != NULL) {
		delete spriteGrid[i * W + j];
		spriteGrid[i * W + j] = NULL;
	}

	spriteGrid[i * W + j] = palette->getCopyById(id);//spriteMap[id]->clone();
	spriteGrid[i * W + j]->parent = this;
	spriteGrid[i * W + j]->setUpdateFuncion(palette->getOriginById(id)->getUpdateFuncion());
	//memcpy(spriteGrid[i * W + j], spriteMap[id], sizeof(Sprite));
	//spriteGrid[i * W + j]->rootScene = rootScene;
	//if(grid[i*W+j])

	//spriteGrid[i * W + j]->onUpdate(0.2);

	Vec2 poss = position + Vec2(anchor.x * tileW, anchor.y * tileH) + Vec2(j * tileW, i * tileH);
	//poss
	SDL_Rect box = { ceil(poss.x + j * tileW * (scale - 1)),
		ceil(poss.y + i * tileH * (scale - 1)) , ceil(tileW * scale), ceil(tileH * scale) };

	Sprite* tmp = spriteGrid[i * W + j];

	tmp->setBox(box);
	tmp->getPolygonCollider()->scale(scale);
}

void Grid::resetPositions() {
	cout << W << endl;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {

			if (spriteGrid[i * W + j] == NULL) continue;

			//setTileOn(i, j, grid[i * W + j]);

			Vec2 pos = position + Vec2(anchor.x * tileW, anchor.y * tileH) + Vec2(j * tileW, i * tileH);

			SDL_Rect box = { ceil(pos.x + j * tileW * (scale - 1)),
				ceil(pos.y + i * tileH * (scale - 1)) , ceil(tileW * scale), ceil(tileH * scale) };

			//delete spriteGrid[i * W + j];
			//spriteGrid[i * W + j] = new Sprite(*spriteMap[grid[i * W + j]]);
			Sprite* tmp = spriteGrid[i * W + j];

			tmp->setBox(box);
			tmp->setRotation(0);
			//cout << tmp->getRotation() << endl;
		}
	}
}

void Grid::setTileOn(int i, int j, int id) {
	if (i < 0 || j < 0 || i >= H || j >= W || id > palette->getSize() || id < 0) return;

	grid[i * W + j] = id;

	setTileSprite(i, j, id);
}

void Grid::setTiles(vector<int> ids, int h, int w) {
	int len = ids.size();
	resetSize(H, W);
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			int cur = i * W + j;

			if (cur < len) {
				setTileOn(i, j, ids[cur]);
				
			}
		}
	}
}

void Grid::setTiles(vector<string> names, int h, int w) {
	vector<int> ids;
	for (auto n : names) {

	}
}

Sprite* Grid::getTileAt(int x, int y) {
	if(x >= 0 && y >= 0 && x < W && y < H)
		return spriteGrid[y * W + x];
	return NULL;
}


/*
 返回瓦片id
*/
//int Grid::addNewTile(string name, Sprite* sprite) {
//	tileTypeNums++;
//	spriteMap[tileTypeNums] = sprite;
//	//cout << name << endl;
//	sprite->setName(name);
//	sprite->parent = this;
//	return tileTypeNums;
//}

void Grid::draw() {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (grid[i * W + j]) {
				//spriteGrid[i * W + j]->drawCollider = true;
				spriteGrid[i * W + j]->draw();
			}
		}
	}
}

Vec2 Grid::pointInGridXY(Vec2 point) {
	int x = point.x / (tileW * scale);
	int y = point.y / (tileW * scale);
	return Vec2(x, y);
}

/*
	该函数并不会改变tile在网格中的实际位置
*/
bool Grid::tileMoveTo(Vec2 posOfTile, Vec2 endPosition, double speed) {
	Node* sp = getTileAt(posOfTile.x, posOfTile.y);
	if (sp == NULL) {
		//cout << "?" << endl;
		return false;
	}
	Vec2 realEndPos = Vec2(endPosition.x * tileW * scale + anchor.x * tileW * scale, endPosition.y * tileH * scale + anchor.y * tileH * scale);
	//cout << realEndPos << endl;
	return sp->moveTo(realEndPos, speed);

}

/*
	该函数并不会改变tile在网格中的实际位置
*/
Vec2 Grid::tileMoveToAndCollide(Vec2 posOfTile, Vec2 endPosition, double speed, bool slide) {
	Node* sp = getTileAt(posOfTile.x, posOfTile.y);
	if (sp == NULL) return Vec2(0, 0);
	Vec2 realEndPos = Vec2(endPosition.x * tileW *scale + anchor.x * tileW , endPosition.y * tileH * scale - anchor.y * tileH * scale);
	return sp->moveToAndCollide(realEndPos, speed, slide);
}

void Grid::onUpdate(double dt) {
	//for (int i = 0; i < W * H; i++){
	//	if (grid[i]) {
	//		
	//		if (spriteGrid[i]->name == "spike_up") {
	//			cout << (static_cast<Spike*>(spriteGrid[i]))->getName();
	//		}
	//		
	//	}	
	//}
}
