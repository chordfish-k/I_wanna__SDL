#pragma once
#ifndef GRID_H
#define GRID_H

#include "Sprite.h"
#include <vector>
#include "SDL.h"
#include "Palette.h"

using namespace std;

class Sprite;

class Grid : public Node {
private:
	vector<int> grid;
	vector<Sprite*> spriteGrid;
	Palette *palette;
	//map<int, Sprite*> spriteMap;
	int tileTypeNums;
	int H;
	int W;
	int tileH;
	int tileW;
	double scale;
public:
	Grid(int H, int W, int tileH, int tileW, double scale = 1);
	void setPalette(Palette* p) { palette = p; }
	void setTileSprite(int i, int j, int id);
	void setTileOn(int i, int j, int id);
	void setTiles(vector<int> ids, int h, int w);
	void setTiles(vector<string> ids, int h, int w);
	Sprite* getTileAt(int x, int y);
	vector<Node*> getAllChildren();
	string getNodeType() { return "Grid"; }
	int getH() { return H; }
	int getW() { return W; }
	int getTileH() { return tileH; }
	int getTileW() { return tileW; }
	void resetSize(int H, int W);
	void onUpdate(double dt);
	void resetPositions();
	Vec2 pointInGridXY(Vec2 point);

	//该函数并不会改变tile在网格中的实际位置
	bool tileMoveTo(Vec2 posOfTile, Vec2 endPosition, double speed);
	//该函数并不会改变tile在网格中的实际位置
	Vec2 tileMoveToAndCollide(Vec2 posOfTile, Vec2 endPosition, double speed, bool slide = false);
	void draw();

};


#endif