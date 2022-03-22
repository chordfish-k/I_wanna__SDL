#pragma once
#include "Sprite.h"

using namespace std;

class Spike : public Sprite{
private:
	bool hasTrap = false;

	int cntttt;
	int st;
public:

	Spike(int type = 0);

	void onUpdate(double dt);
	Spike* clone() { return new Spike(*this); };
};

