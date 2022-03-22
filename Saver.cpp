#include "Saver.h"
#include "Rectangle.h"
#include "Game.h"

Saver::Saver(string sceneName, Vec2 pos) {
	//this->name = "saver";

	this->enableCollider = true;
	//this->drawCollider = true;
	
	this->open("res/block/saver_0.bmp");

	ani = new Animation(50);
	ani->add("res/block/saver_1.bmp");
	ani->add("res/block/saver_0.bmp");

	Polygon2D rect = Rectangle2D(Vec2(0, 0), Vec2(-12, -12), Vec2(12, 12));
	this->setPolygonCollider(rect);

	this->saveSceneName = sceneName;
	this->savePosition = pos;
	this->isSet = false;

}




void Saver::saverPoint() {
	if (this->isSet) return;
	this->isSet = true;
	Game::game->setPlayerRespawnPoint(this->saveSceneName, this->savePosition);
	runAnimation(ani);
}

void Saver::onUpdate(double dt) {
	Sprite::onUpdate(dt);
}