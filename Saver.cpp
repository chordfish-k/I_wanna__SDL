#include "Saver.h"
#include "Rectangle.h"
#include "Game.h"

Saver::Saver(string sceneName, Vec2 pos) {
	//this->name = "saver";

	this->enableCollider = true;
	this->drawCollider = true;
	
	this->open("res/block/saver_0.png");

	ani = new Animation(50);
	ani->add("res/block/saver_1.png");
	ani->add("res/block/saver_0.png");

	Polygon2D rect = Rectangle2D(Vec2(0, 0), Vec2(-12, -12), Vec2(12, 12));
	this->setPolygonCollider(rect);

	this->saveSceneName = sceneName;
	this->savePosition = pos;
	this->isSet = false;

}


////Saver::Saver(Saver& s) : Sprite(s) {
////	//cout << "copy: " << s.name << endl;
////	this->setTexture(s.getTexture());
////	this->before = s.before;
////	this->after = s.after;
////	this->enableCollider = s.enableCollider;
////	this->collider = Polygon2D(*s.getPolygonCollider());
////	this->drawCollider = s.drawCollider;
////	this->saveSceneName = s.saveSceneName;
////	this->savePosition = s.savePosition;
////	this->isSeted = s.isSeted;
////	//this->setName("saver");
//	//cout << "name:"<<s.saveSceneName << endl;
//	//this->saveSceneName = s.saveSceneName;
//	//this->savePosition = s.savePosition;
//	//this->isSeted = s.isSeted;
////}
//Sprite* Saver::clone() {
//	
//	Saver *s = new Saver(*this);
//	
//	s->saveSceneName = this->saveSceneName;
//	cout << "a "<<s->saveSceneName << endl;
//	//s->savePosition = this->savePosition;
//	//cout << "TOm:" << s->saveSceneName << endl;
//	return s;
//}


void Saver::saverPoint() {
	if (this->isSet) return;
	this->isSet = true;
	Game::game->setPlayerRespawnPoint(this->saveSceneName, this->savePosition);
	runAnimation(ani);
}