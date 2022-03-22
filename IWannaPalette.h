#pragma once

#ifndef IWANNNA_PALETTE_H
#define IWANNNA_PALETTE_H

#include "Palette.h"
#include "Spike.h"
#include "Saver.h"

class IWannaPalette : public Palette {
private:
	Sprite* wall = NULL;
	Sprite* grass = NULL;
	Sprite* floor3 = NULL;

	Spike* spkup = NULL;
	Spike* spkright = NULL;
	Spike* spkdown = NULL;
	Spike* spkleft = NULL;
	
	
public:
	IWannaPalette() {

		grass = new Sprite(Vec2(0, 0), "res/block/floor_1.bmp");
		wall = new Sprite(Vec2(0, 0), "res/block/floor_2.bmp");
		

		spkup = new Spike(0);
		spkright = new Spike(1);
		spkdown = new Spike(2);
		spkleft = new Spike(3);



		wall->enableCollider = true;
		grass->enableCollider = true;

		spkup->enableCollider = true;
		spkright->enableCollider = true;
		spkdown->enableCollider = true;
		spkleft->enableCollider = true;

		

		//add("air", new Sprite());
		add("floor", grass);
		add("floor", wall);
		add("spike", spkup);
		add("spike", spkright);
		add("spike", spkdown);
		add("spike", spkleft);

		for (int i = 1; i < tileNums; i++) {
			cout << spriteMap[i]->name << spriteMap[i]->getTexture() << endl;
		}
	}

	~IWannaPalette() {
		//delete wall, grass, spkup, spkright;
		//wall = grass = spkup = spkright = NULL;
	}
};

#endif