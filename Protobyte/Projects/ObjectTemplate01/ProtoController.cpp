#include "ProtoController.h"

using namespace ijg;

void ProtoController::init() {
	background(0.7);
	theta = 0;
	c = ProtoBlock(Vec3f(0.5, 0.5, 0.5), Vec3f(50, 50, 50), Dim3f(10, 10, 10), Col4f(0.5, 0.7, 0.2, 1));
}

void ProtoController::run() {
}

void ProtoController::display() {
	push();
	scale(100, 100, 100);
	rotate(theta, Vec3f(1.0, 0.0, 0.0));
	c.display();
	pop();
	theta += 0.1;
}

void ProtoController::mousePressed() {
	println("Working.");
}