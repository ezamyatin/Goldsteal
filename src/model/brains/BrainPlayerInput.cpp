#include "BrainPlayerInput.h"

BrainPlayerInput::BrainPlayerInput(InputData const* input) {
	this->input = input;
}

void BrainPlayerInput::decide(IBody* body) {
	InputData in = *input;
	body->changes = [body, in]() {
		if (in.pUp || in.pDown)
			body->velocity.y += in.pUp ? -IBody::ACCELERATION : IBody::ACCELERATION;
		else {
			if (body->velocity.y > 0) {
				body->velocity.y -= IBody::ACCELERATION;
				body->velocity.y = std::max(0.0, body->velocity.y);
			} else {
				body->velocity.y += IBody::ACCELERATION;
				body->velocity.y = std::min(0.0, body->velocity.y);
			}
		}

		if (in.pLeft || in.pRight)
			body->velocity.x += in.pRight ? IBody::ACCELERATION : -IBody::ACCELERATION;
		else {
			if (body->velocity.x > 0) {
				body->velocity.x -= IBody::ACCELERATION;
				body->velocity.x = std::max(0.0, body->velocity.x);
			} else {
				body->velocity.x += IBody::ACCELERATION;
				body->velocity.x = std::min(0.0, body->velocity.x);
			}
		}

		
		body->velocity.x = std::min(body->velocity.x, IBody::MAX_SPEED);
		body->velocity.x = std::max(body->velocity.x, -IBody::MAX_SPEED);
		
		body->velocity.y = std::min(body->velocity.y, IBody::MAX_SPEED);
		body->velocity.y = std::max(body->velocity.y, -IBody::MAX_SPEED);
		
		if (Geo::greater(body->velocity.len(), 0))
			body->moveState=IBody::STATE_WALK;
		else
			body->moveState=IBody::STATE_IDLE;
		//std::cerr << body->velocity << "\n";
		body->move(body->velocity);
	};
}