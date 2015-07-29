#include "ProtoController.h"

void ProtoController::init() {
	background(0.7);
	//shadowsOn();
	clearColors();
	makeColors();
	assignColors();
	b = ProtoBlock(Vec3f(0, 0, 0), Vec3f(0, 0, 0), Dim3f(10, 10, 10), colors);
}

void ProtoController::run() {
}

void ProtoController::display() {
	push();
	scale(100);
	rotate(135, Vec3f(0.0, 1.0, 0.0));
	b.display();
	pop();
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

void ProtoController::makeColors() {
	red = Col4f(0.85, 0.05, 0.17, 1.0);
	blue = Col4f(0.05, 0.17, 0.43, 1.0);
	white = Col4f(0.98, 0.88, 0.91, 1.0);
}

void ProtoController::assignColors() {
	colors.resize(8);
	colors[0] = blue;
	colors[1] = white;
	colors[2] = white;
	colors[3] = blue;
	colors[4] = red;
	colors[5] = white;
	colors[6] = blue;
	colors[7] = red;
}