#include "ProtoController.h"

void ProtoController::init() {
	setLight(0, { -100, 100, 200 }, { 1, 1, 1 });
	shadowsOn();
	t = Toroid({ 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 }, { 1, 1, 1, 1 }, 36, 36, 125, 45);
	t.setDiffuseMap("ship_plate_rainbow.jpg");
	t.setBumpMap("ship_plate_rainbow.jpg");
	t.setTextureScale({ 0.5f, 0.35f });
	pcg = new ProtoGeomComposite();
	//pcg->init();

	plane = ProtoPlane({ 0 }, { 0 }, { 500, 500 }, { 1, 1, 1, 1 }, 1, 1);
	plane.setDiffuseMap("ship_plate.jpg");
	plane.setTextureScale({ .2f, .2f });
	plane.setBumpMap("ship_plate.jpg");

}

void ProtoController::run() {
}

void ProtoController::display() {
	static float theta = 0.0f;

	setLight(0, { sin(theta += PI/540.0f)*200.0f, 100, 200 }, { 1, 1, 1 });

	beginArcBall();
	//translate(0, 0, -400);

	push();
	translate(0, 0, -300);
	//rotate(180, 0, 1, 0);
	scale(3000);
	plane.display();
	pop();

	rotate(getFrameCount()*.3, { 0, 0, 1 });


	push();
	translate(-300, 200, 190);
	rotate(getFrameCount()*.2, { 1, .2f, 0 });
	t.display();
	pop();

	push();
	translate(300, 200, 190);
	rotate(-getFrameCount()*.2, { 1, .75f, 0 });
	t.display();
	pop();

	push();
	translate(-300, -200, 190);
	rotate(getFrameCount()*1.2, { 1, .05f, 0 });
	t.display();
	pop();

	push();
	translate(300, -200, 190);
	rotate(-getFrameCount()*.2, { 1, 0, 0 });
	rotate(-getFrameCount()*2.2, { 0, 1, 0 });
	rotate(-getFrameCount()*1.2, { 0, 0, 1 });
	t.display();
	pop();

	translate(0, -100, -150);
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