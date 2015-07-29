
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
	enum TestType {
		COLOR,
		FRAME
	};

	float theta;
	int clickNum;

	Col4f red, blue, green, magenta, yellow, cyan, white, black, grey;
	void colorsInit();
	void setColorsAlpha(float newA);

	ProtoBlock blocks[5];
	void protoBlockInit();
	void protoBlockTest(TestType type = COLOR);
	void protoBlockClick();

	ProtoCylinder cyls[5];
	void protoCylInit();
	void protoCylTest(TestType type = COLOR);
	void protoCylClick();

	//TO DO:
		//ProtoSphere
		//ProtoToroid

};

#endif //__PROTOCONTROLLER_H__
