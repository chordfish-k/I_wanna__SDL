#pragma once
#ifndef  PALETTE_H
#define PALETTE_H

#include <map>
#include <string>

using namespace std;

class Sprite;

class Palette {
protected:
	int tileNums;
	map<int, Sprite* > spriteMap;
public:
	//zeroAir: true则id=0用NULL占位, false则id从0开始
	Palette();
	~Palette();
	//返回id
	int add(string name, Sprite* sprite);
	Sprite* getCopyById(int id);
	Sprite* getOriginById(int id);
	int getSize() { return tileNums; };
};

#endif // ! PALETTE_H
