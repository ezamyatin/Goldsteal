#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <tmx/TmxMap.h>
#include <hgeresource.h>
#include <tmx/Tmx.h.in>
                        
#include "IRenderable.h"
#include "IObject.h"
#include "../render/RenderData.h"
#include "LightSource.h"


struct GameState;
struct Environment : IRenderable {
	Environment() {};
	Environment(Tmx::Map const* map, hgeResourceManager* res);
	
	std::vector<IObject*> getObjects() const {return objs;}

	std::vector<LightSource*> getLightSources() const {return lightSources;}

	void addObject(IObject* obj) {objs.push_back(obj);}
	void addLightSource(LightSource* ls) {lightSources.push_back(ls); ls->setEnvironment(this);}
	int getWidth() const {return width;}
	int getHight() const {return hight;}
	void render(HGE* hge, Camera const* cam);
	Ring calcVisible(Vector const& o);
	void frame();
	friend struct GameState;

private:
	std::vector<IObject*> objs;
	std::vector<LightSource*> lightSources;
	int width;
	int hight;
	Render::EnvironmentData rData;
};
#endif