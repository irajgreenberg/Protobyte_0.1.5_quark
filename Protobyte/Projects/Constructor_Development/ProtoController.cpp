#include "ProtoController.h"

void ProtoController::init() {
	light0.setPosition(Vec3f(0, 100, 500));
	a = Block(Col4f(1.0, 0.0, 0.0, 1.0));
	b = Block(200, 125, 25, Col4f(0.0, 0.0, 1.0, 1.0));
	c = Block(Dim3f(50, 30, 100), Col4f(0.0, 1.0, 0.0, 1.0));
	//implement default parameter for color of ProtoBlock?

	e = Cylinder(Col4f(1.0, 0.0, 0.0, 1.0));
	f = Cylinder(30, 30, 200, Col4f(0.0, 0.0, 1.0, 1.0));
	g = Cylinder(Dim3f(100, 100, 20), Col4f(0.0, 1.0, 0.0, 1.0));
	h = Cylinder(50.0, 50.0, 200.0);
	i = Cylinder(Dim3f(30.0, 30.0, 5.0));

	theta = 0.0;
}

void ProtoController::run() {
}

void ProtoController::display() {
	push();
	translate(-100, 0, 0);
	scale(75);
	rotate(theta, Vec3f(0.3, 0.3, 0.4));
	//a.display();
	e.display();
	pop();

	push();
	translate(100, 0, 0);
	rotate(theta, Vec3f(0.3, 0.3, 0.4));
	//b.display();
	f.display();
	pop();

	push();
	translate(0, -150, 0);
	rotate(theta, Vec3f(0.3, 0.3, 0.4));
	//c.display();
	g.display();
	pop();

	push();
	translate(0, 150, 0);
	rotate(theta, Vec3f(0.3, 0.3, 0.4));
	h.display();
	pop();

	push();
	translate(-200, 200, 0);
	rotate(theta, Vec3f(0.3, 0.3, 0.4));
	i.display();
	pop();

	push();
	translate(-200, -200, 0);
	rotate(theta, Vec3f(0.3, 0.3, 0.4));
	//j.display();
	pop();

	push();
	translate(150, 150, 0);
	rotate(theta, Vec3f(0.3, 0.3, 0.4));
	//k.display();
	pop();
	
	theta += 0.1;
}

// Key and Mouse Events
void ProtoController::keyPressed(){
}

void ProtoController::mousePressed(){
}

void ProtoController::mouseRightPressed(){
}

void ProtoController::mouseReleased(){
}

void ProtoController::mouseRightReleased(){
}

void ProtoController::mouseMoved(){
}

void ProtoController::mouseDragged(){
}

// Window Events
void ProtoController::onResized(){
}

void ProtoController::onClosed(){
}