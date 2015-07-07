
#ifndef __PROTOCONTROLLER_H__
#define __PROTOCONTROLLER_H__

#include <iostream>
#include "ProtoBaseApp.h"
#include "BrittCube.h"
#include "TestShape.h"
#include "TestGeom.h"

using namespace ijg;

class ProtoController : public ProtoBaseApp {

public:
	void init();
	void run();
	void display();

	void mousePressed();

private:
	//BrittCube b;
	ProtoBlock c;
	TestShape s;
	float theta;
	
};

#endif //__PROTOCONTROLLER_H__
