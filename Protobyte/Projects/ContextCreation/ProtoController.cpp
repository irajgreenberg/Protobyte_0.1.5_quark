#include "ProtoController.h"

void ProtoController::init() {
	//setLight(0, { 0, 100, 600 }, { 1, 1, 1 });
	shadowsOn();
	t = Toroid({ 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 }, { 1, 1, 1, 1 }, 36, 36, 125, 45);
	t.setDiffuseMap("ship_plate_rainbow.jpg");
	t.setBumpMap("ship_plate_rainbow.jpg");
	pcg = new ProtoGeomComposite();
	//pcg->init();

	plane = ProtoPlane(Vec3(), Vec3(), Dim2f(500, 500), Col4(1, 1, 1, 1), 1, 1);
	plane.setDiffuseMap("ship_plate_rainbow.jpg");
	plane.setBumpMap("ship_plate_rainbow.jpg");

}

void ProtoController::run() {
}

void ProtoController::display() {
	beginArcBall();
	//translate(0, 0, 4100);


	push();
	translate(0, 0, -500);
	//rotate(180, 0, 1, 0);
	//scale(3000);
	plane.display();
	pop();

	
	push();
	translate(-200, 200, -10);
	//rotate(getFrameCount()*.2, Vec3(1, .2, 0));
	t.display();
	pop();

	push();
	translate(200, 200, -10);
	//rotate(-getFrameCount()*.2, Vec3(1, .75, 0));
	t.display();
	pop();

	push();
	translate(-200, -200, -10);
	//rotate(getFrameCount()*1.2, Vec3(1, .05, 0));
	t.display();
	pop();

	push();
	translate(200, -200, -10);
	rotate(-getFrameCount()*.2, Vec3(1, 0, 0));
	rotate(-getFrameCount()*2.2, Vec3(0, 1, 0));
	rotate(-getFrameCount()*1.2, Vec3(0, 0, 1));
	t.display();
	pop();

	translate(0, 0, -300);
	pcg->display();
	endArcBall();

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