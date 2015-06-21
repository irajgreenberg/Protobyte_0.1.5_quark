
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

private:
	float w = 1400.0;
	float d = 1400.0;
	static const int cols = 40;
	static const int lays = 40;

	ProtoBlock block;
	std::vector<Vec3> scl;
	std::vector<Vec3> pos;
	std::vector<Vec2> ang;
};

#endif //__PROTOCONTROLLER_H__
