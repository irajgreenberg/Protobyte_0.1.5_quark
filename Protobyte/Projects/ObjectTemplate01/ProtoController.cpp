#include "ProtoController.h"

using namespace ijg;

void ProtoController::init() {
	background(0.7);
	theta = 0;
	a = ProtoBlock(Vec3f(0, 0, 0), Vec3f(0, 0, 0), Dim3f(10, 10, 10), Col4f(0.0, 0.0, 1.0, 1.0));
	b = TestBlock(Vec3f(0, 0, 0), Vec3f(0, 0, 0), Dim3f(10, 10, 10), Col4f(1.0, 0.0, 0.0, 1.0));
	println("a:");
	println(a);
	println("b:");
	println(b);
	println("c:");
	println(c);
}

void ProtoController::run() {
}

void ProtoController::display() {
	push();
	scale(100, 100, 100);
	rotate(theta, Vec3f(0.0, 1.0, 0.0));
	a.display();
	pop();

	push();
	translate(0, -100, 0);
	scale(100, 100, 100);
	rotate(theta, Vec3f(0.0, 1.0, 0.0));
	b.display();
	pop();

	push();
	translate(0, -200, 0);
	scale(100, 100, 100);
	rotate(theta, Vec3f(0.0, 1.0, 0.0));
	//c.display();
	pop();

	theta += 0.1;
}

void ProtoController::mousePressed() {
	println("Working.");
}