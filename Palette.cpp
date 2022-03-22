#include "Palette.h"
#include <string>
#include "Sprite.h"

using namespace std;

Palette::Palette() {

	this->tileNums = 0;
	spriteMap[0] = new Sprite();
}

int Palette::add(string name, Sprite* sprite) {
	this->tileNums++;
	spriteMap[this->tileNums] = sprite->clone();
	spriteMap[this->tileNums]->setName(name);
	//cout << name << endl;
	return this->tileNums;
}

Sprite* Palette::getCopyById(int id) {
	if(id >=0 && id <= this->tileNums)
		return spriteMap[id]->clone();
	return NULL;
}

Sprite* Palette::getOriginById(int id) {
	if (id >= 0 && id <= this->tileNums)
		return spriteMap[id];
	return NULL;
}

Palette::~Palette() {
	delete spriteMap[0];
	spriteMap[0] = NULL;
}