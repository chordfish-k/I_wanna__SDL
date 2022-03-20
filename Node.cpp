#include "Node.h"
#include "Grid.h"

vector<Node*> Node::getAllChildren() {
	vector<Node*> res;
	for (auto n : children) {
		if (n.second == NULL) continue;
		res.push_back(n.second);
		if (n.second->getNodeType() != "Grid") {
			for (auto nn : n.second->getAllChildren()) {
				res.push_back(nn);
			}
		}
		else {
			for (auto nn : (dynamic_cast<Grid*> (n.second))->getAllChildren()) {
				res.push_back(nn);
			}
		}
		
	}
	return res;
}

vector<Polygon2D*> Node::getAllCollider() {
	vector<Polygon2D*> res;
	for (auto ch : getAllChildren()) {
		if (ch->getNodeType() == "Sprite") {
			Sprite* sp = dynamic_cast<Sprite*>(ch);
			if (sp->enableCollider && sp->getPolygonCollider() != NULL) {
				res.push_back(sp->getPolygonCollider());
			}
		}
	}
	return res;
}

void Node::addChild(string name, Node* n) {
	children[name] = n;
	n->setName(name);
	n->rootScene = rootScene;
	n->parent = this;
}

void Node::onUpdate(double dt) {
	
	for (auto n : children) {
		if (n.second != NULL) {
			n.second->onUpdate(dt);
		}
	}
}


void Node::move(Vec2 velocity) {
	setPosition(getPosition() + velocity);
}

void Node::deleteChild(string name) {
	if (children[name] != NULL) {
		delete children[name];
		children[name] = NULL;
	}
}


void Node::deleteAllChildren() {
	children.clear();
}

/*
  该函数将返回一个受力方向
*/
Vec2 Node::moveAndCollide(Vec2 velocity, bool gothrough, bool slide) {
	Vec2 res(0, 0);
	Vec2 colliVec(0, 0), all(0, 0);

	Node* p = this;
	Vec2 tmp = p->getPosition();

	p->setPosition(tmp + velocity);

	//cout << getNodeType() << endl;
	if (getNodeType() == "Sprite") {
		Sprite* sp = dynamic_cast<Sprite*>(this);
		if (!sp->enableCollider)
			return Vec2(0, 0);
	}


	
	if(rootScene == NULL) return Vec2(0, 0);

	vector<Polygon2D* > ch = rootScene->getAllCollider();
	int len = ch.size();


	for (auto n : ch) {
		//if ((n->name) != name)
		if(collideWith.count(n->name))
		if (p->getPolygonCollider()->checkCollision(n, colliVec)) {
			onCollided(n->parent);
			all = all + colliVec;
		}
	}
	//cout << all << endl;
	res = all;

	if (gothrough)
		return res;

	double err = 1; //使用遍历搜出刚好不发生碰撞的位置。。有点莽，理论上可以用二分改进
	bool flag = false;
	int cnt = 0;
	while (cnt < 50 && (fabs(all.x) > eps || fabs(all.y) > eps))
	{
		p->setPosition(tmp);
		if (fabs(all.x) > eps || fabs(all.y) > eps) {
			double angle = all.angleWith(velocity);

			velocity = Vec2(fabs(all.x) < eps ? 0 : velocity.x, fabs(all.x) < eps ? velocity.y : 0);
			if (slide) {
				if (angle < 90) {
					velocity = velocity.project(all.normalize());
					p->setPosition(tmp + velocity * err);
				}
				else if (angle > 90) {
					velocity = velocity.project(-all.normalize());
					p->setPosition(tmp + velocity * err);
				}
			}
			else {
				p->setPosition(tmp + velocity * err);
			}
			err -= 0.15 * cnt;
			cnt++;
		}
		all = Vec2(0, 0);
		for (int i = 0; i < len; i++) {
			Polygon2D* n = ch[i];
			if (collideWith.count(n->name))
			if (p->getPolygonCollider()->checkCollision(n, colliVec)) {
				all = all + colliVec;
			}
		}
	}
	return res.perpendicular();
}

/*
	返回是否到达
*/
bool Node::moveTo(Vec2 endPosition, double speed) {
	Vec2 sub = endPosition - getPosition();
	//double l = (sub).normalize();
	if (fabs(sub.normSquare()) < speed * speed) {
		sub = Vec2(0, 0);
		setPosition(endPosition);
		return true;
	}
	Vec2 sp = (sub).normalize() * speed;
	move(sp);
	return false;
}


Vec2 Node::moveToAndCollide(Vec2 endPosition, double speed, bool slide) {
	Vec2 sub = endPosition - getPosition();
	if (sub.normSquare() < speed * speed) {
		sub = Vec2(0, 0);
	}
	Vec2 sp = (sub).normalize() * speed;
	return moveAndCollide(sp, slide);
}

Node* Node::clone() {
	Node* n = new Node(*this);
	return n;
}
