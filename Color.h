#pragma once
#ifndef _COLOR_H_
#define _COLOR_H_

#include <iostream>
#include <SDL.h>

#include "Tool.h"

using namespace std;

class Color {

public:
	Uint8 r=0, g=0, b=0, a=0;
	static Color BLACK;
	static Color WHITE;
public:

	Color(Uint8 r=0, Uint8 g=0, Uint8 b=0, Uint8 a=255) :r(r), g(g), b(b), a(a) {}
	//Color& operator=(const Color& c) {
	//	/*r = c.r;
	//	g = c.g;
	//	b = c.b;
	//	a = c.a;*/
	//	return *this;
	//}
	Color operator*(double k) {
		r = (Uint8)Tool::Clamp(r * 1.0 * k / 255, 0, 255);
		g = (Uint8)Tool::Clamp(g * 1.0 * k / 255, 0, 255);
		b = (Uint8)Tool::Clamp(b * 1.0 * k / 255, 0, 255);
		a = (Uint8)Tool::Clamp(a * 1.0 * k / 255, 0, 255);
	}


	static Color random() {
		return Color(Tool::Rand(0, 255), Tool::Rand(0, 255), Tool::Rand(0, 255), 255);
	}

	friend ostream& operator<<(ostream& out, const Color& c) {
		out << "<Color>(" << (int)c.r << "," << (int)c.g << "," << (int)c.b << "," << (int)c.a << ")";
		return out;
	}

	double pointWith(Color& c) {
		return r * c.r + g * c.g + b * c.b + a * c.a;
	}

};



#endif