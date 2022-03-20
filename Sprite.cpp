#include "Sprite.h"


Sprite::Sprite(Sprite& sp) {
	name = sp.name;
	img = sp.img;
	box = sp.box;

	collider = sp.collider;
	collider.parent = this;
	//cout << (collider.getAllPoints().size()) << endl;
	anchor = sp.anchor;
	enableCollider = sp.enableCollider;
	drawCollider = sp.drawCollider;
	position = sp.position;
	color = sp.color;
}

Sprite* Sprite::clone() {
	return new Sprite(*this);
}

void Sprite::open(string imgPath) {
	defaultImg = Tool::openRescource(imgPath);
	img = defaultImg;

	if (img == nullptr)
		cout << "[Error]Failed to load image:" << imgPath << IMG_GetError() << endl;
	SDL_Rect pos;
	pos.x = position.x;
	pos.y = position.y;
	SDL_QueryTexture(img, NULL, NULL, &pos.w, &pos.h); //获取宽高属性

	Vec2 offset(pos.w / 2, pos.h/2);
	vector<Vec2> ps;
	position = position - offset;
	ps.push_back(position + Vec2(0, 0));
	ps.push_back(position + Vec2(0 + pos.w, 0));
	ps.push_back(position + Vec2(0 + pos.w, 0 + pos.h));
	ps.push_back(position + Vec2(0, 0 + pos.h));


	box = pos;
	collider = Polygon2D(ps, collider.getPosition());
	collider.parent = this;
	//Vec2 realPos(pos.x - pos.w * anchor.x, pos.y - pos.h * anchor.y);
	//setPosition(realPos);
	//setPosition(position);
	collider.setColor(Color(0, 0, 255, 255));
}

Sprite::~Sprite() {
	SDL_DestroyTexture(img);
}

SDL_Texture* Sprite::getTexture() {
	return img;
}

void Sprite::setPolygonCollider(Polygon2D& c) {
	collider = c;
	collider.parent = this;
}

void Sprite::setName(string newName) {
	collider.name = newName;
	name = newName;
}

void Sprite::setPosition(Vec2 p) {
	if (p != position) {
		collider.setPosition(p);
		position = p;
		box.x = p.x;
		box.y = p.y;
	}
	
}

void Sprite::setBox(SDL_Rect r) {
	box = r;
	setPosition(Vec2(r.x, r.y));
}

void Sprite::setAnchor(Vec2 a) {
	if (a.x < eps || a.y < eps || a.x > 1 || a.y > 1) {
		return;
	}
	anchor = a;
}


void Sprite::setScale(double k) {
	if (k == 1.0) return;
	collider.scale(k);
	box.w *= k;
	box.h *= k;
	scale.x = scale.y = k;
}



void Sprite::draw() {
	draw(box);
	/*Draw::SetColor(0,0,255,255);
	SDL_RenderDrawLine(Draw::ren, position.x, position.y + 3, position.x, position.y - 3);
	SDL_RenderDrawLine(Draw::ren, position.x + 3, position.y, position.x - 3, position.y);*/
}

void Sprite::draw(SDL_Rect targetRect) {
	if (!visable || img == NULL) return;

	targetRect.x -= anchor.x * box.w;
	targetRect.y -= anchor.y * box.h;

	SDL_RendererFlip flip1 = flipX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	SDL_RendererFlip flip2 = flipY ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
	SDL_RenderCopyEx(Draw::ren, img, NULL, &targetRect, rotation, NULL, flip1);

	if (drawCollider)
		getPolygonCollider()->draw();
}

void Sprite::cloneTo(Sprite* sp) {
	if (sp == NULL)
		//*sp = Sprite(*this);
		*sp = Sprite(position);
	if (sp != NULL) {
		sp->img = img;
		sp->box = box;
		sp->collider = Polygon2D( collider);
		//cout << (sp->collider.getAllPoints().size()) << endl;
		sp->anchor = anchor;
		sp->enableCollider = enableCollider;
		sp->position = position;
		sp->color = color;
	}

}

void Sprite::runAnimation(Animation *anime) {
	if (anime == curAnimation) return;
	curAnimation = anime;
	curAnimation->setCurrentFrame(0);
}

void Sprite::onUpdate(double dt) {
	if (curAnimation != NULL && !curAnimation->checkEnd()) {
		img = curAnimation->getCurrentClip();
		curAnimation->next();
	}
}

void Sprite::rotateTo(double angle, double speed) {
	angle = Tool::Clamp(angle, -180, 180);
	double sub = Tool::Clamp(angle - rotation, -180, 180);
	if (fabs(sub) <= angle * speed) {
		getPolygonCollider()->rotateBy(sub);
		rotation = angle;
		//cout << rotation << endl;
		return;
	}
	
	getPolygonCollider()->rotateBy((sub) * speed);
	rotation = rotation + (sub) * speed;
}

void Sprite::setRotation(double angle) {
	rotation = angle;
	getPolygonCollider()->rotateBy(0 - getPolygonCollider()->getRotation());
}