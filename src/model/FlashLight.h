#ifndef FLASHLIGHT_H
#define FLASHLIGHT_H
#include "LightSource.h"
#include "IBody.h"
#include <hge.h>
#include "Camera.h"
#include "../Geometry.h"
#include <cmath>
#include <hgeresource.h>

struct Environment;
struct FlashLight : LightSource {	
	FlashLight(hgeResourceManager* res, IBody* body, float angle) : LightSource(res), owner(body) {
		sn = sinf(angle);
		cs = cosf(angle);
	};
	
	virtual void frame();
	
	virtual void setEnvironment(Environment const* env);
	
	virtual void render(HGE* hge, Camera* cam) {LightSource::renderLight(hge, cam);}
	
	virtual void renderLamp(HGE* hge, Camera* cam) {}

private:
	IBody* owner;
	float sn;
	float cs;
};
#endif