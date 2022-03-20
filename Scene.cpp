#include "Scene.h"
#include "Draw.h"
#include "Game.h"


void Scene::onUpdate(double dt) {

	for (auto n : rootNode.getAllChildren()) {
		n->onUpdate(dt);
		//cout << n->name << endl;
	}
	draw();

};

void Scene::onLoad() {

}

void Scene::onExit() {

}


void Scene::draw() {
	Draw::CleanCanvas();

	for (auto n : rootNode.getAllChildren()) {
		if(n != NULL)
			(n)->draw();
	}

	Draw::RefreshCanvas();
}


vector<Node*> Scene::getAllChildren() {
	return rootNode.getAllChildren();

}

vector<Polygon2D*> Scene::getAllCollider() {
	return rootNode.getAllCollider();
}

void Scene::addChild(string name, Node* n) {
	rootNode.addChild(name, n);
	
}
