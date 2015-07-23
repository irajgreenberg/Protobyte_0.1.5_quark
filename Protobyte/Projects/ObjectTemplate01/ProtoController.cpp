#include "ProtoController.h"

using namespace ijg;

void ProtoController::init() {
	std::cout << "HI." << std::endl;
	background(0.7);
	setColors();
	setRainbow();
	setHalf();
	name = "Brittni";
	theta = 0;
	a = ProtoBlock(Vec3f(0, 0, 0), Vec3f(0, 0, 0), Dim3f(10, 10, 10), blue);
	b = TestBlock(name);
	c = TestBlock(red);
	d = TestBlock(half);
	e = TestBlock(Vec3f(100, 100, 0), Vec3f(45, 0, 0), Dim3f(100, 100, 100));
	f = TestBlock(Vec3f(100, 200, 0), Vec3f(0, 30, 0), Dim3f(50, 50, 50), green);
	g = TestBlock(Vec3f(100, 200, 0), Vec3f(0, 30, 0), Dim3f(50, 50, 50), rainbow);
}

void ProtoController::run() {
}

void ProtoController::display() {
	//Block A
	push();
	translate(-300, 0, 0);
	scale(75, 75, 75);
	rotate(theta, Vec3f(1.0, 0.0, 0.0));
	a.display();
	pop();

	//Block B
	push();
	translate(-200, 0, 0);
	scale(75, 75, 75);
	rotate(-theta, Vec3f(1.0, 0.0, 0.0));
	b.display();
	pop();

	//Block C
	push();
	translate(-100, 0, 0);
	scale(75, 75, 75);
	rotate(theta, Vec3f(1.0, 0.0, 0.0));
	c.display();
	pop();

	//Block D
	push();
	scale(75, 75, 75);
	rotate(-theta, Vec3f(1.0, 0.0, 0.0));
	d.display();
	pop();

	//Block E
	push();
	translate(100, 0, 0);
	scale(75, 75, 75);
	rotate(theta, Vec3f(1.0, 0.0, 0.0));
	e.display();
	pop();

	//Block F
	push();
	translate(200, 0, 0);
	scale(75, 75, 75);
	rotate(-theta, Vec3f(1.0, 0.0, 0.0));
	f.display();
	pop();

	//Block G
	push();
	translate(300, 0, 0);
	scale(75, 75, 75);
	rotate(theta, Vec3f(1.0, 0.0, 0.0));
	g.display();
	pop();

	theta += 0.1;
}

void ProtoController::mousePressed() {
	println("Working.");
	a.setColor(black);
	b.setColor(red);
	c.setColor(blue);
}

void ProtoController::setColors() {
	red = Col4f(1.0, 0.0, 0.0, 1.0);
	blue = Col4f(0.0, 0.0, 1.0, 1.0);
	green = Col4f(0.0, 1.0, 0.0, 1.0);
	magenta = Col4f(1.0, 0.0, 1.0, 1.0);
	cyan = Col4f(0.0, 1.0, 1.0, 1.0);
	yellow = Col4f(1.0, 1.0, 0.0, 1.0);
	white = Col4f(1.0, 1.0, 1.0, 1.0);
	black = Col4f(0.0, 0.0, 0.0, 1.0);
}

void ProtoController::setRainbow() {
	if (rainbow.size() > 0) {
		rainbow.clear();
	}
	rainbow.push_back(red);
	rainbow.push_back(yellow);
	rainbow.push_back(green);
	rainbow.push_back(cyan);
	rainbow.push_back(blue);
	rainbow.push_back(magenta);
	rainbow.push_back(black);
	rainbow.push_back(white);
}

void ProtoController::setHalf() {
	if (half.size() > 0) {
		half.clear();
	}
	half.push_back(blue);
	half.push_back(cyan);
	half.push_back(cyan);
	half.push_back(blue);
	half.push_back(blue);
	half.push_back(cyan);
	half.push_back(cyan);
	half.push_back(blue);
}