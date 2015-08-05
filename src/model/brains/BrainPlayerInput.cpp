#include "BrainPlayerInput.h"
#include "../GameState.h"


BrainPlayerInput::BrainPlayerInput(InputData const* input) {
	this->input = input;
}

void BrainPlayerInput::decide(IBody* body) {
	InputData in = *input;

	body->dir = Geo::Vector(in.mX, in.mY) - body->pos;
	//double st = clock();
	std::vector<Geo::Polygon> objs;
	for (IObject* obj : body->state->getEnvironment()->getObjects())
		if (obj->isObstruct())
			objs.push_back(obj->getBounds());
	body->visible = Geo::visibilityPolygon(body->pos, objs, body->state->getEnvironment()->getWidth(), body->state->getEnvironment()->getHight());
	
	if (in.pUp || in.pDown)
		body->velocity.y += in.pUp ? -IBody::ACCELERATION : IBody::ACCELERATION;
	else {
		if (body->velocity.y > 0) {
			body->velocity.y -= IBody::ACCELERATION;
			body->velocity.y = std::max(0, body->velocity.y);
		} else {
			body->velocity.y += IBody::ACCELERATION;
			body->velocity.y = std::min(0, body->velocity.y);
		}
	}

	if (in.pLeft || in.pRight)
		body->velocity.x += in.pRight ? IBody::ACCELERATION : -IBody::ACCELERATION;
	else {
		if (body->velocity.x > 0) {
			body->velocity.x -= IBody::ACCELERATION;
			body->velocity.x = std::max(0, body->velocity.x);
		} else {
			body->velocity.x += IBody::ACCELERATION;
			body->velocity.x = std::min(0, body->velocity.x);
		}
	}

		
	body->velocity.x = std::min(body->velocity.x, IBody::MAX_SPEED);
	body->velocity.x = std::max(body->velocity.x, -IBody::MAX_SPEED);
		
	body->velocity.y = std::min(body->velocity.y, IBody::MAX_SPEED);
	body->velocity.y = std::max(body->velocity.y, -IBody::MAX_SPEED);
		
	if ((body->velocity.len2() > 0))
		body->moveState=IBody::STATE_WALK;
	else
		body->moveState=IBody::STATE_IDLE;
	//std::cerr << body->velocity << "\n";
}
