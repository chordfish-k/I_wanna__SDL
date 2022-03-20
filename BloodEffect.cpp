#include "BloodEffect.h"
#include "Tool.h"
#include "Draw.h"

BloodEffect::BloodEffect(Vec2 pos) {
	position = pos - Vec2(8, 16);

	timer.start();
	startTick = timer.getTicks();
}

void BloodEffect::onUpdate(double dt) {
	if (isEnd) return;


	if (!isBurstEnd) {
		int n = max(0, Tool::Rand(num - numRange, num + numRange));

		for (int i = 0; i < n; i++) {
			Piece p;
			int L = Tool::Rand(2, 8);
			p.rect = { (int)position.x, (int)position.y, L, L };
			double angle = Tool::Rand((startAngle - angleRange) * 10, (startAngle + angleRange) * 10) / 10.0;
			p.speed = Vec2(angle) * Tool::Rand((startSpeed - speedRange) * 100, (startSpeed + speedRange) * 100) / 100.0;
			//p.speed.x *= (p.speed.y / startSpeed);

			p.color = Color(Tool::Rand(150, 255), 0, 0, 255);

			pieces.push_back(p);
		}


		if (!isEnd && timer.getTicks() - startTick > burstDuration) {
			isBurstEnd = true;
		}
	}
	

	for (auto& p : pieces) {
		p.speed = p.speed + gravity * dt;
		p.setPosition(p.getPosition() +  p.speed * dt);
	}

	if (!isEnd && timer.getTicks() - startTick > existingDuration) {
		isEnd = true;
	}

	
}

void BloodEffect::draw() {
	if (isEnd) return;

	for (auto& p : pieces) {
		Draw::SetColor(p.color);
		SDL_RenderFillRect(Draw::ren, &p.rect);
	}
}