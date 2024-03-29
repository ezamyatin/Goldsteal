#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <hgeresource.h>
#include <hge.h>
#include <vector>
#include <tmx/Tmx.h.in>

#include "Environment.h"                   
#include "IRenderable.h"
#include "Camera.h"
#include "IBody.h"
#include "../InputData.h"
#include "../render/RenderData.h"

struct GameState : IRenderable {
	GameState(Tmx::Map const* map, hgeResourceManager* res);
	    
	std::vector<IBody*> getBodies() {return bodies;}
	
	void addBody(IBody* body) {body->setGameState(this); bodies.push_back(body);}	
	
	void setHero(IBody* body) {body->setGameState(this); this->hero=body;}	
	
	void render(HGE* hge, Camera* cam);
	
	void setEnvironment(Environment* env) {this->env=env;}
	
	Environment* getEnvironment() {return env;}
	
	IBody* getHero() {return hero;}
	
	void process(IBody* body);
	
	void frame();
	
private:
	Render::GameStateData rData;
	
	std::vector<IBody*> bodies;
	Environment* env;
	IBody* hero;	
};
#endif