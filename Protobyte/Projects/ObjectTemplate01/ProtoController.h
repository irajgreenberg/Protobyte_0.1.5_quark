#ifndef __PROTOCONTROLLER_H__
#define __PROTOCONTROLLER_H__

#include <iostream>
#include "ProtoBaseApp.h"
#include "TestBlock.h"

using namespace ijg;

class ProtoController : public ProtoBaseApp {

public:
	void init();
	void run();
	void display();

	void mousePressed();

private:
	Col4f red, blue, green, magenta, cyan, yellow, white, black;
	std::vector<Col4f> rainbow;
	std::vector<Col4f> half;

	ProtoBlock a;

	TestBlock b, c, d, e, f, g;

	float theta;

	std::string name;

	void setColors();
	void setRainbow();
	void setHalf();
	
};
#endif //__PROTOCONTROLLER_H__