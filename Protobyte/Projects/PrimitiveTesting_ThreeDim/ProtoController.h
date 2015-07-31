
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
		FRAME,
		PNTS
	};

	enum ConstType {
		PROTO,
		BRITT
	};

	float theta;
	int clickNum;

	Col4f red, blue, green, magenta, yellow, cyan, white, black, grey;
	void colorsInit();
	void setColorsAlpha(float newA);

	ProtoBlock blocks[5];
	void protoBlockInit(ConstType type = PROTO);
	void protoBlockTest(TestType type = COLOR);
	void protoBlockClick();

	ProtoCylinder cyls[5];
	void protoCylInit(ConstType type = PROTO);
	void protoCylTest(TestType type = COLOR);
	void protoCylClick();

	ProtoSphere spheres[5];
	void protoSphereInit(ConstType type = PROTO);
	void protoSphereTest(TestType type0 = COLOR, ConstType type1 = PROTO);
	void protoSphereClick();

	ProtoToroid tors[5];
	void protoTorInit();
	void protoTorTest(TestType type = COLOR);
	void protoTorClick();

	ProtoBlock block;
	void blockTest(TestType type = COLOR);

	ProtoCylinder cylinder;
	void cylinderTest(TestType type = COLOR);

	ProtoSphere sphere;
	void sphereTest(TestType type = COLOR);

	ProtoToroid toroid;
	void toroidTest(TestType type = COLOR);
};

#endif //__PROTOCONTROLLER_H__
