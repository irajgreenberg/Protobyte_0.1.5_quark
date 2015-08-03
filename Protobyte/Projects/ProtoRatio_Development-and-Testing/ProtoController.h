
#ifndef __PROTOCONTROLLER_H__
#define __PROTOCONTROLLER_H__

#include <iostream>
#include "ProtoBaseApp.h"
#include "ProtoRatio2.h"
#include "ProtoRatio3.h"

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

	ProtoRatio2 r;
	ProtoRatio2 r1;

};

#endif //__PROTOCONTROLLER_H__
