#include "ProtoController.h"

void ProtoController::init() {
	light1.setPosition(Vec3(-30, 0, -200));

//ProtoSphere(int spines, int spineNodes, ;const ProtoColor4f col4, const std::string& textureImageURL, float textureScale)
	s = ProtoSphere(26, 26, Col4(.4, .4, .4, 1), "corroded_red.jpg", .2);
	s.setSpecularMaterial(Col4(1, 1, 1, 1));
	s.setShininess(20);
	s.setBumpMap("corroded_red.jpg");
}

void ProtoController::run() {
}

void ProtoController::display() {
	beginArcBall();
	scale(300);
	s.display();
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