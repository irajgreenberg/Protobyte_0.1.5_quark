#include "ProtoController.h"

void ProtoController::init() {
	a = Block(Col4f(1.0, 0.0, 0.0, 1.0));
	b = Block(200, 125, 25, Col4f(0.0, 0.0, 1.0, 1.0));
	c = Block(Dim3f(50, 30, 100), Col4f(0.0, 1.0, 0.0, 1.0));
	d = Block(Vec3f(75, 20, 300), Col4f(0.0, 1.0, 1.0, 1.0));

	e = Cylinder(Col4f(1.0, 0.0, 0.0, 1.0));
	f = Cylinder(30, 30, 200, Col4f(0.0, 0.0, 1.0, 1.0));

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
	c.display();
	pop();

	push();
	translate(0, 150, 0);
	rotate(theta, Vec3f(0.3, 0.3, 0.4));
	d.display();
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