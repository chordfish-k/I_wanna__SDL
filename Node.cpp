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

	//Polygon2D pol(*p->getPolygonCollider());
	//Vec2 po = tmp;
	//Polygon2D npol({pol.points[0] +po, pol.points[1] + po, pol.points[2] + po + velocity, pol.points[3] + po + velocity});
	/*cout << "::" << po << endl;
	cout << npol.points[0] << endl;
	cout << npol.points[1] << endl;
	cout << npol.points[2] << endl;
	cout << npol.points[3] << endl;*/
	p->setPosition(tmp + velocity);
	//npol.draw();
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
		//if (npol.checkCollision(n, colliVec)) {
		if (p->getPolygonCollider()->checkCollision(n, colliVec)) {
			onCollided(n->parent, colliVec);

			Sprite* other =dynamic_cast<Sprite*> (n->parent);
			if (other && other->enableCollider) {
				other->onCollided(this, - colliVec);
			}

			
			all = all + colliVec;
		}
	}
	//cout << all << endl;
	res = all;

	if (gothrough)
		return res;

	Vec2 lastPos = tmp + velocity;

	double err = 1; //使用遍历搜出刚好不发生碰撞的位置。。有点莽，理论上可以用二分改进
	bool flag = false;
	int cnt = 0;
	while (cnt < 50 && (fabs(all.x) > eps || fabs(all.y) > eps))
	{
		//p->setPosition(tmp);
		if (fabs(all.x) > eps || fabs(all.y) > eps) {
			double angle = all.angleWith(velocity);

			velocity = Vec2(fabs(all.x) < eps ? 0 : velocity.x, fabs(all.x) < eps ? velocity.y : 0);
			
			//------------------------
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
			//------------------------
			else {
				p->setPosition(tmp + velocity * err);
				//lastPos = tmp + velocity * err;
				//npol = Polygon2D({ pol.points[0], pol.points[1], pol.points[2] + velocity * err, pol.points[3] + velocity * err });

			}
			err -= 0.15 * cnt;
			cnt++;
		}
		all = Vec2(0, 0);
		for (int i = 0; i < len; i++) {
			Polygon2D* n = ch[i];
			if (collideWith.count(n->name))
			//if (npol.checkCollision(n, colliVec)) {
			if (p->getPolygonCollider()->checkCollision(n, colliVec)) {
				all = all + colliVec;
				//cout << "?b" << endl;
			}
		}
	}
	//p->setPosition(lastPos);
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
	return new Node(*this);
}
