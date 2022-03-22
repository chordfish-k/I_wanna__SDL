#pragma once

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cmath>
#include <SDL.h>
#include "Vec2.h"
#include "Collider.h"
#include "Drawable.h"
#include <set>

using namespace std;

class Scene;

class Node : public Collider, public Drawable {
protected:
	Vec2 position;
	Vec2 scale;
	map<string, Node*> children;
	
public:
	Scene* rootScene = NULL;
	Node* parent = NULL;
	string name = "_";
	Vec2 anchor;
	set<string> collideWith;
public:
	Node(Vec2 position = Vec2(0, 0)) 
		:position(position), scale(Vec2(1, 1)), children() {};
	virtual ~Node() {};
	virtual void setPosition(Vec2 p) { position = p; }; //设置中心点位置
	virtual Vec2 getPosition() { return position; };
	virtual void setScale(Vec2 s) { scale = s; }; //设置拉伸
	virtual Vec2 getScale() { return scale; };
	virtual void onUpdate(double dt);
	virtual void setName(string name) { this->name = name; }
	virtual string getName() { return name; }
	virtual string getNodeType() { return "Node"; }
	virtual vector<Node*> getAllChildren();
	virtual vector<Polygon2D*> getAllCollider();
	virtual void addChild(string name, Node* n);
	virtual void deleteChild(string name);
	virtual void deleteAllChildren();
	virtual void draw() {}
	virtual void move(Vec2 velocity);
	virtual Vec2 moveAndCollide(Vec2 velocity, bool gothrough = false, bool slide = false);
	virtual bool moveTo(Vec2 endPosition, double speed);
	virtual Vec2 moveToAndCollide(Vec2 endPosition, double speed, bool slide = false);
	virtual void onCollided(Node* other, Vec2 dir) {};
	virtual Node* clone();
};





#endif