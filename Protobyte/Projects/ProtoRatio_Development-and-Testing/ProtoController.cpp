#include "ProtoController.h"

void ProtoController::init() {
	println(r);
	r.setElem1(5);
	r.setElem0(6);
	println(r.getElem0());
	println(r.getElem1());
	println(r.getUnit());
	r.setElem1(1);
	println(r);

}

void ProtoController::run() {
}

void ProtoController::display() {
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