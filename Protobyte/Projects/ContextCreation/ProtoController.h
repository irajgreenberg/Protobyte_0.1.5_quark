
#ifndef __PROTOCONTROLLER_H__
#define __PROTOCONTROLLER_H__

#include <iostream>
#include "ProtoBaseApp.h"
#include "ProtoGeomComposite.h"

using namespace ijg;

class ProtoController : public ProtoBaseApp {

public:
	void init();
	void run();
	void display();

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
	ProtoGeomComposite* pcg;

};

#endif //__PROTOCONTROLLER_H__
