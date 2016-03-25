#include "ProtoController.h"

void ProtoController::init() {

	light0.setPosition(Vec3f(0, 150, 450));
	light0.setIntensity(Vec3f(.85, .85, .85));

	light1.setPosition(Vec3f(-10, -400, 450));
	light1.setIntensity(Vec3f(1, 1, 1));

	setShadowsOn(true);
	rect = Rect(0, 0, 130, 130, Col4f(.5, .75, .85, 1.0));
	//toroid = Toroid(Vec3(), Vec3(), Dim3f(100, 100, 100), Col4f(0, 0, 0, 1), 36, 12, 1, .25);
	toroid = new Toroid();

	toroid->textureOn();
	toroid->setBumpMap("corroded_metal.jpg");
	//toroid.loadBumpMapTexture("yellow2.jpg");
	toroid->setTextureScale(Vec2f(.05));
	toroid->setAmbientMaterial(Col4f(.3, .85, .3, 1.0));
	toroid->setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	toroid->setSpecularMap("yellow2.jpg");
	toroid->setTextureScale(Vec2f(.05));
	toroid->setShininess(109);
	

	//toroid = Toroid(200, 45);
	//toroid = Toroid(300);
}

void ProtoController::run() {
}

void ProtoController::display() {
	translate(0, 0, 0);
	//scale(rect.getSize().w, rect.getSize().h, 0);
	beginArcBall();
	//rect.display();
	scale(150);
	toroid->display();
	endArcBall();
}

// Key and Mouse Events
void ProtoController::keyPressed(){
	trace("key =", key, " scancode =", scancode, " action =", action);
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