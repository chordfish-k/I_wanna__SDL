#include "Player.h"
#include "Rectangle.h"
#include "Game.h"
#include "BloodEffect.h"
#include "GameOverSprite.h"
#include "Saver.h"
#include "Bullet.h"
#include <sstream>

Player::Player() {

	this->open("res/player/player_idle_0.png");

	animation_idle = new Animation(5); //5tick / frame
	animation_idle->add("res/player/player_idle_0.png")
		->add("res/player/player_idle_1.png")
		->add("res/player/player_idle_2.png")
		->add("res/player/player_idle_3.png")
		->setLoop(true);

	animation_run = new Animation(5);
	animation_run->add("res/player/player_run_0.png")
		->add("res/player/player_run_1.png")
		->add("res/player/player_run_2.png")
		->add("res/player/player_run_3.png")
		->setLoop(true);

	animation_jump = new Animation(5); 
	animation_jump->add("res/player/player_jump_0.png")
		->add("res/player/player_jump_1.png")
		->setLoop(true);

	animation_fall = new Animation(5);
	animation_fall->add("res/player/player_fall_0.png")
		->add("res/player/player_fall_1.png")
		->setLoop(true);

	anchor = Vec2(0.5, 0.5);

	Polygon2D rect = Rectangle2D(Vec2(0, 7), Vec2(-5, -7), Vec2(5, 8));
	this->setPolygonCollider(rect);
	this->setScale(1.5);

	reset();

	collideWith.insert("floor");
	collideWith.insert("spike");
	collideWith.insert("saver");
}

void Player::reset() {
	this->runAnimation(animation_idle);
	this->enableCollider = true;
	//this->drawCollider = true;
	this->state = State::IDLE;
	this->visable = true;
	this->jumpCnt = 0;
	this->velocity = Vec2(0, 0);
	this->XTargetVel = this->YTargetVel = Vec2(0, 0);
	this->jumping = false;
	this->children.clear();
}


void Player::checkMove(double dt) {
	if (Game::game->keys['A']) {
		XTargetVel.x = -speed;
		velocity.x = -speed;
	}
	else if (Game::game->keys['D']) {
		XTargetVel.x = speed;
		velocity.x = speed;
	}
	else {
		XTargetVel.x = 0;
		velocity.x = 0;
	}

	//如果碰墙就不给速度了
	if (re.x != 0) {
		XTargetVel.x = 0;
	}

	if (re.y != 0) {
		jumpCnt = 1;
	}

	if (Game::game->keysJust[VK_SPACE]) {
		if (!jumping) {
			if (jumpCnt++ >= 2) {
				jumping = true;
			}

			velocity.y = -jumpSpeed;
			YTargetVel.y = 0;
		}
	}
	if (state == State::JUMP && !Game::game->keys[VK_SPACE]) {
		//cout << "A" << endl;
		velocity.y = velocity.y * 0.8;
		YTargetVel.y = jumpSpeed * 0.8;
	}


	YTargetVel = YTargetVel.moveToword(Vec2(0, jumpSpeed * 0.8), 0, gravity * dt);
	Vec2 kvel = XTargetVel + YTargetVel; //目标合速度
	//---------

	bool move = (fabs(XTargetVel.x) > eps || fabs(XTargetVel.y) > eps);
	bool jp = (fabs(YTargetVel.y) > eps);

	if (move || jp) {
		velocity = velocity.moveToword(kvel, (move ? acceleration : friction) * dt, (jp ? YFirction : gravity) * dt);
	}
	else {
		velocity = velocity.moveToword(Vec2(0, 0), friction * dt, gravity * dt);
	}



	//应用运动
	re = moveAndCollide(velocity * dt).normalize();
	Vec2 vp = getPosition();

	if (fabs(re.x) > eps || fabs(re.y) > eps) {

		if (fabs(re.y) > eps) {
			velocity.y = 0;
		}

	}
	if (fabs(re.y) == 1.0) {
		YTargetVel = Vec2(0, jumpSpeed);
		jumpCnt = 0;
		jumping = false;
	}

	changeAnime();
}


void Player::checkShoot(double dt) {
	if (Game::game->keysJust['J']) {
		cout << "shoot" << endl;
		Sprite* b = new Bullet(flipX);
		b->setPosition(getPosition());
		stringstream ss;
		string name;
		ss << "bullet";
		ss << Tool::Rand(0, 100);
		ss >> name;
		addChild(name, b);
	}
}


void Player::onUpdate(double dt) {
	Sprite::onUpdate(dt);

	if (state == State::DEATH) {
		return;
	}
	
	checkMove(dt);
	checkShoot(dt);
	
}

void Player::changeAnime() {
	Vec2 dpos;//位移量
	Vec2 pos = getPosition();
	if (hasLastpoint) {
		dpos = pos - lastPosition;
		lastPosition = pos;

	}
	else {
		lastPosition = pos;
		hasLastpoint = true;
	}


	//设置翻转
	if (fabs(dpos.x) > eps + 0.05)
		flipX = dpos.x < -eps;
	//---更改状态 start---
	Animation* tmpAnime = animation_idle;

	//cout << dpos << endl;

	if (dpos.y < -eps) {
		setState(State::JUMP);
		tmpAnime = animation_jump;
	}
	else if (dpos.y > eps) {
		setState(State::FALL);
		tmpAnime = animation_fall;
	}
	else {
		if (fabs(dpos.x) > eps+0.1) {
			setState(State::RUN);;
			tmpAnime = animation_run;
		}
		else {
			setState(State::IDLE);
			tmpAnime = animation_idle;
		}
	}
	runAnimation(tmpAnime);
	//---更改状态 end---
}

void Player::onCollided(Node* other) {
	
	if (other->name != "floor") {
		//cout << other->name << endl;
	}
	if (other->name.substr(0, 5) == "spike") {
		setState(State::DEATH);

		Node* eff = new BloodEffect(this->position);
		addChild("Blood", eff);
		visable = false;

		Node* over = new GameOverSprite();
		addChild("GameOver", over);
	}

	else if (other->getName() == "saver") {
		//Game::game->setPlayerRespawnPoint("scene1", {50, 300});
		Saver* s = (Saver*)other;
		s->saverPoint();

	}
		
	
}

void Player::setState(State newState) {
	if (state != State::DEATH && state != newState) {
		state = newState;
	}
}

