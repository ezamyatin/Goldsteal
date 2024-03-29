#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include "IObject.h"
#include "Camera.h"
#include <hge.h>
#include <hgeresource.h>
struct Environment;
struct GameState;
struct LightSource : IObject {
	LightSource(hgeResourceManager* res) {
		lightShader = res->GetShader("LightShader");
	}	
	
	LightSource(Tmx::Object const* o, hgeResourceManager* res) : IObject(o, res) {
		lightShader = res->GetShader("LightShader");
		pos.x = (long long int)o->GetX();
		pos.y = (long long int)o->GetY();
		pos.owner = this;
	}
	
	virtual void setEnvironment(Environment const* env);

	virtual void render(HGE* hge, Camera* cam);
	
	virtual void renderLight(HGE* hge, Camera* cam);
	
	virtual void renderLamp(HGE* hge, Camera* cam);
	
	virtual void frame();
	
	bool isEnable() const {return enabled;}

	friend struct GameState;
	friend struct Environment;

protected:
	Vertex pos;
	bool enabled=true;
	Environment const* env;
	HSHADER lightShader;
};

#endif