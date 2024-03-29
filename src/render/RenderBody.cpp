#include "../model/IBody.h"
#include "RenderData.h"
#include <hgeanim.h>
#include <hge.h>
#include "help.h"
#include "../model/GameState.h"
#include "../Geometry.h"

void IBody::render(HGE *hge, Camera const* cam) {
	
	Box r(pos, radius);
	Box c(cam->getPos().x-cam->CAMERA_WIDTH/2, cam->getPos().y-cam->CAMERA_HIGHT/2, cam->CAMERA_WIDTH, cam->CAMERA_HIGHT);
	
	if (!geo::intersects(r, c))
		return;
	                        
	hgeAnimation& a = rData.get(moveState);
	
	double dt = hge->Timer_GetDelta();
	
	if (moveState == rData.lastState)
		a.Update(dt);
	else
		a.Play();
	
	float x = pos.x;
	float y = pos.y;
	float sn = dir.x/sqrt((float)geo::distance2({0,0}, dir));
	float cs = -dir.y/sqrt((float)geo::distance2({0,0}, dir));
	cam->convertGS(x, y);
	
	a.RenderEx1(x, y, sn, cs, cam->KX*rData.width/a.GetWidth(), cam->KY*rData.hight/a.GetHeight());
	rData.lastState = moveState;
	
}
