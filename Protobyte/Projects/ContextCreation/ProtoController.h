
#ifndef __PROTOCONTROLLER_H__
#define __PROTOCONTROLLER_H__

#include <iostream>
#include "ProtoBaseApp.h"
#include "ProtoGeomComposite.h" // new class to test - integrate in PBA eventually

#include "btBulletDynamicsCommon.h"

#include "ProtoRootBall.h"

using namespace ijg;

class ProtoController : public ProtoBaseApp {

public:
	void init();
	void run();
	void display();

	void testBullet();

	// Key and Mouse Events
	void keyPressed();
	void mousePressed();
	void mouseRightPressed();
	void mouseReleased();
	void mouseRightReleased();
	void mouseMoved();
	void mouseDragged();

	// Window Events
	void onResized();
	void onClosed();

private:
	Toroid t;
	ProtoPlane plane;
	ProtoGeomComposite* pcg;
	ProtoRootBall* pBall;

};

#endif //__PROTOCONTROLLER_H__