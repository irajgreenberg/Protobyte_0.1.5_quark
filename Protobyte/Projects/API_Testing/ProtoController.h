#ifndef __PROTOCONTROLLER_H__
#define __PROTOCONTROLLER_H__

#include <iostream>
#include "ProtoBaseApp.h"

using namespace ijg;

class ProtoController : public ProtoBaseApp {

public:
	//Variables
	Col4f red = Col4f(1.0, 0, 0, 1.0);
	Col4 blue = Col4(0, 0, 1.0, 1.0);
	Col4 green = Col4(0.0, 1.0, 0.0, 1);
	Col4f black = Col4f(0, 0, 0, 1);
	Col4f white = Col4f(1, 1, 1, 1);
	Col4f pink = Col4f(1, 0, 1, 1);
	Col4f yellow = Col4f(1, 1, 0, 1);
	Col4f cyan = Col4f(0, 1, 1, 1);

	int topCornerX;
	int topCornerY;

	float theta;

	int x, y;
	int x1, y1;

	int xSpeed = 5;
	int ySpeed = -5;

	//Functions
	void init();
	void run();
	void display();
	void mousePressed();

	void edgeTesting();
	void matrixTesting();
	void scaleTesting();

	void rectTestA();
	void rectTestB();
	void rectTestC();
	void rectTestD();

	void ellipseTestA();
	void ellipseTestB();
	void ellipseTestC();
	void ellipseTestD();

	void quadTestA();
	void quadTestB();

	void centerShapes();

	void spinnySquare();

	void pixelTesting();

	void protoEllipseTest();

	void protoBlockTest();

	void viewTest();

	ProtoEllipse e0;

	Vec3 pos;
	Vec3 rot;
	Dim2f size;
	Col4f color;
	int detail;

	ProtoBlock b0;
	ProtoBlock b1;

	Toroid t0;

	ProtoBlock blocks[5];

	std::vector<Col4f> colors;

	int clickCount = 0;

private:

};

#endif //__PROTOCONTROLLER_H__