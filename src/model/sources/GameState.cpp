#include "../GameState.h"

GameState::GameState(Tmx::Map const* map, hgeResourceManager* res) {
	env = new Environment(map, res);

	for (Tmx::ObjectGroup const* ob : map->GetObjectGroups()) {
		if (ob->GetName() != "BodyLayer")
			continue;
		for (Tmx::Object const* o : ob->GetObjects()) {
			if (o->GetType() == "Body") {
				addBody(new IBody(o, res));
			} else if (o->GetType() == "Hero") {
				setHero(new IBody(o, res));
			}
		}
	}
	rData.target1 = res->GetTarget("GameStateTarget1");
	if (rData.target1 == 0) {
		std::cerr << "Can't find GameStateTarget1\n";
		exit(0);
	}

	rData.target2 = res->GetTarget("GameStateTarget2");
	if (rData.target2 == 0) {
		std::cerr << "Can't find GameStateTarget2\n";
		exit(0);
	}

	rData.target3 = res->GetTarget("GameStateTarget3");
	if (rData.target3 == 0) {
		std::cerr << "Can't find GameStateTarget3\n";
		exit(0);
	}

	rData.blurShader = res->GetShader("BlurShader");
	if (rData.blurShader == NULL) {
		std::cerr << "Can't find BlurShader\n";
		exit(0);
	}

	rData.kSize = 9;
	rData.dirX[0] = 0.002f, rData.dirX[1] = 0.f;
	rData.dirY[0] = 0.f, rData.dirY[1] = 0.002f;
	rData.sigma = 3.f;
	for (int i = -rData.kSize/2; i <= rData.kSize/2; ++i) {
		rData.kernel[i+rData.kSize/2] = rData.gaussian(rData.dirX[0]*i, rData.sigma);
	}

}

void GameState::process(IBody* body) {
	body->pos += body->velocity;
	/*Geo::Vector& vel = body->velocity; 
	if (vel.len2() == 0)
		return; 
	
	Geo::Vector newPos = body->pos + vel;
	bool was = false;
	std::vector<Geo::Vector> newVels;
	newVels.push_back(vel);

	for (IObject* obj : env->objs) {
		if ((obj->center - body->pos).len2() >= ((std::max(body->radius2, obj->radius2))<<2))
			continue; 
		for (int i = 0; i < obj->bounds.size(); ++i) {
			Geo::Segment s(obj->bounds[i], obj->bounds[i+1]);
			int d = Geo::distance2(newPos, s);
			if (d < body->radius2) {
				Geo::Vector n((s.b-s.a).normal());
				Geo::Vector part(n*(vel^n));
				Geo::Vector vel1(vel);
				vel1 *= n.len2();
				Geo::Vector res=vel1-part;
				res.x = n.x > 0 ? (((res.x + n.len2() - 1) / n.len2())) : res.x / n.len2();
				res.y = n.y > 0 ? (((res.y + n.len2() - 1) / n.len2())) : res.y / n.len2();
                //res.x = n.x > 0 ? (res.x >= 0 ? ((res.x + n.len2() - 1) / n.len2()) : ((res.x - n.len2() + 1) / n.len2())) : res.x / n.len2();
                newVels.push_back(res);
				was = true;
			}
		}
		if (was)
			break;
	}

	newVels.push_back({0,0});
	for (Geo::Vector& nvel : newVels) {		
		newPos = body->pos + nvel;
		bool ok = true;
		for (IObject* obj : env->objs) {
			if (Geo::distance2(newPos, obj->bounds) < body->radius2)
				ok = false;
		}
		if (ok) {
			body->pos = newPos;
			vel = nvel;
			break;
		}
	}           */                                      
	body->pos.x = std::max((long long)body->radius, body->pos.x);
	body->pos.x = std::min((long long)env->getWidth() - body->radius, body->pos.x);

	body->pos.y = std::max((long long)body->radius, body->pos.y);
	body->pos.y = std::min((long long)env->getHight() - body->radius, body->pos.y);
}

void GameState::frame() {
	hero->frame();
	for (IBody* b : bodies)
		b->frame();

	process(hero);
	for (IBody* body : bodies) 
		process(body);
	env->frame();
}




























