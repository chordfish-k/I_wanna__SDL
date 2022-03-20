#include "Animation.h"
#include "Tool.h"

Animation::Animation(double deltaFrame) :deltaFrame(deltaFrame) {

}

Animation::~Animation() {
	for (auto i : clips) {
		SDL_DestroyTexture(i);
	}
}

Animation* Animation::add(string path) {
	SDL_Texture* img = Tool::openRescource(path);
	clips.push_back(img);
	clipNum++;
	return this;
}

Animation* Animation::setLoop(bool isLoop) {
	loop = isLoop;
	return this;
}

void Animation::next() {
	framCounter++;
	if (framCounter < deltaFrame) return;

	framCounter = 0;
	currentClip = (++currentClip) % clipNum;
	//cout << currentClip << endl;
	if (currentClip == 0 && !loop) {
		isEnd = true;
	}
}

SDL_Texture* Animation::getCurrentClip() {
	return clips[currentClip];
}

bool Animation::checkEnd() {
	return isEnd;
}

Animation* Animation::setCurrentFrame(int index) {
	currentClip = Tool::Clamp(index, 0, clipNum-1);
	return this;
}
