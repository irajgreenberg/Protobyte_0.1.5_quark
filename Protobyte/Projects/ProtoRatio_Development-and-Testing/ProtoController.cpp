#include "ProtoController.h"

void ProtoController::init() {
	println(r);
	r = ProtoRatio2(2, 3);
	println(r);
	r.setElem1(5);
	r.setElem0(6);
	r.setSampleSize(100);
	println(r.getElem0());
	println(r.getElem1());
	println(r.getUnit());
	println(r.getSampleSize());
	println(r.getElemSample0());
	println(r.getElemSample1());
	r = ProtoRatio2(1, 1, 100);
	println(r);

	r1 = ProtoRatio2(2, 3, 45);
	println(r1);

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