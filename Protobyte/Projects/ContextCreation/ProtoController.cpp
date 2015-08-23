#include "ProtoController.h"

void ProtoController::init() {
	t = Toroid(36, 36, 125, 45);

}

void ProtoController::run() {
}

void ProtoController::display() {
	push();
	translate(-200, 200, 0);
	rotate(getFrameCount()*.2, Vec3(1, .2, 0));
	t.display();
	pop();

	push();
	translate(200, 200, 0);
	rotate(-getFrameCount()*.2, Vec3(1, .75, 0));
	t.display();
	pop();

	push();
	translate(-200, -200, 0);
	rotate(getFrameCount()*1.2, Vec3(1, .05, 0));
	t.display();
	pop();

	push();
	translate(200, -200, 0);
	rotate(-getFrameCount()*.2, Vec3(1, 0, 0));
	rotate(-getFrameCount()*2.2, Vec3(0, 1, 0));
	rotate(-getFrameCount()*1.2, Vec3(0, 0, 1));
	t.display();
	pop();

	//compositeObj.display();  --> push, trans, obj1.display(), pop, push, trans, obj2.display(), pop,
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