#pragma once

#ifndef DRAWABLE_H
#define  DRAWABLE_H
#include "Color.h"

class Drawable {
protected:
	Color color;

public:
	Drawable() : color(Color::WHITE) {};
	Drawable(Drawable& d) : color(d.color) {};
	virtual void draw() = 0;
	virtual void setColor(Color c) { color = c; };
	virtual Color getColor() { return color; }
};

#endif