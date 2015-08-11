#include "ProtoController.h"

void ProtoController::init() {
	a = Block(Col4f(1.0, 0.0, 0.0, 1.0));
	b = Block(Col4f(0.0, 0.0, 1.0, 1.0), 200, 120, 25);
	theta = 0.0;
}

void ProtoController::run() {
}

void ProtoController::display() {
	push();
	translate(-100, 0, 0);
	scale(75);
	rotate(theta, Vec3f(0.3, 0.3, 0.4));
	a.display();
	pop();

	push();
	translate(100, 0, 0);
	rotate(theta, Vec3f(0.3, 0.3, 0.4));
	b.display();
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