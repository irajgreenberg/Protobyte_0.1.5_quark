
#ifndef __PROTOCONTROLLER_H__
#define __PROTOCONTROLLER_H__

#include <iostream>
#include "ProtoBaseApp.h"

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
	//COLORS

	//ProtoColor4

	void setColors_4();

	ProtoColor4<float> red_f;
	ProtoColor4f blue_f;
	Col4f black_f;
	Col4 grey_f;
	Col4 white_f;

	ProtoColor4<int> red_i;
	ProtoColor4i blue_i;
	Col4i black_i;
	Col4i white_i;

	ProtoColor4<long> red_L;
	ProtoColor4<long> blue_L;
	Col4L black_L;
	Col4L white_L;

	ProtoColor4<short> red_s;
	ProtoColor4<short> blue_s;
	Col4s black_s;
	Col4s white_s;
	
	//ProtoColor3
};

#endif //__PROTOCONTROLLER_H__
