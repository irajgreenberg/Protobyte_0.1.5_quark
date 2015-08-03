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

	r1 = Ratio2(2, 3, 45);
	println(r1);

	println(rA);

	rB.setElem0(10);
	rB.setElem1(5);
	rB.setElem2(3);
	rB.setSampleSize(300);

	println(rB.getElem0());
	println(rB.getElem1());
	println(rB.getElem2());
	println(rB.getUnit());
	println(rB.getSampleSize());
	println(rB.getElemSample0());
	println(rB.getElemSample1());
	println(rB.getElemSample2());
	
	rC = ProtoRatio3(1, 2, 3, 200);
	println(rC);

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