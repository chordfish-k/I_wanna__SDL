#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <string>
#include <map>
#include <SDL.h>

#include "Node.h"
#include "Timer.h"
#include "Polygon.h"
#include "Grid.h"


class Scene {
protected:
	Node rootNode;
	//map<string, Node*> childen;
	const int SCREEN_FPS = 60;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
	//每秒钟定时器的帧数
	LTimer fpsTimer;
	//每秒帧数上限定时器
	LTimer capTimer;
	int frameTicks;
public:
	bool isEnd = false;
	//Game* game = NULL;
public:
	Scene() 
		: isEnd(false), frameTicks(0) { 
		rootNode = Node(); 
		rootNode.rootScene = this;
		rootNode.name = "root";
		rootNode.parent = NULL;
	};
	//virtual vector<Node*> getAllChildren();
	//virtual void addChild(string name, Node* n);
	virtual void onLoad();
	virtual void onLoad(Vec2 playerPosition) { onLoad(); };
	virtual void onExit();
	virtual void onUpdate(double dt);
	virtual void reset() {};
	virtual void draw();
	virtual void setRootNode(Node node) {
		rootNode = node;
	}
	virtual void addChild(string name, Node* n);
	virtual vector<Node*> getAllChildren();
	virtual vector<Polygon2D*> getAllCollider();
};



#endif
