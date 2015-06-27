#include "ProtoController.h"

void ProtoController::init() {
	rect = Rect(0, 0, 130, 130, Col4f(.5, .75, .85, 1.0));
}

void ProtoController::run() {
}

void ProtoController::display() {
	translate(0, 0, 0);
	scale(rect.getSize().w, rect.getSize().h, 0);
	beginArcBall();
	rect.display();
	endArcBall();
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