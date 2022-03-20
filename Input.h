#pragma once

#ifndef INPUT_H
#define INPUT_H
#include <map>
#include <windows.h>
#include "Draw.h"
using namespace std;

namespace Input {

	map<int, bool> mp;
	bool hasInput = false;

	bool windowOnTop() {
		return Draw::hwnd == GetForegroundWindow();
	}

	bool isKeyPress(unsigned key) {
		if(windowOnTop())
			return GetKeyState(key) >> 8;
		return false;
	}
}

#endif