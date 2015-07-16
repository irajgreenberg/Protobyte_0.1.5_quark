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
	ProtoBlock c;
	TestBlock d;
	float theta;
	
};
#endif //__PROTOCONTROLLER_H__