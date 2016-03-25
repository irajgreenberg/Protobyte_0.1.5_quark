#include "ProtoController.h"

float theta = 0.0;
Vec2 vecs[23];


const int LEN = 200;
Vec2 ptVecs[LEN];
Col4 ptCols[LEN];


void ProtoController::init() {

	for (int i = 0; i < 23; i++){
		vecs[i] = Vec2(cos(theta)*random(100, 200), sin(theta)*random(100, 200));
		theta += TWO_PI / 23;
	}

	for (int i = 0; i < LEN; i++){
		ptVecs[i] = Vec2(random(-1200, 1200), random(-1200, 1200));
		ptCols[i] = Col4(random(), random(), random(), 1.0);
	}
}

void ProtoController::run() {
}

void ProtoController::display() {
	background(1);
	beginArcBall();
	//fill(1, 1, 0, 1);
	//stroke(.2, 1, .3);
	//strokeWeight(5);
	////rect(-100, 100, 200, 200);

	//translate(0, 0, 2);
	//stroke(.75, .3, .1);
	//strokeWeight(3);
	//fill(1, .5, .1);
	//beginShape(POLYGON);
	//for (int i = 0; i < 23; i++){
	//	vertex(vecs[i].x, vecs[i].y);
	//}
	//endShape(CLOSE);

	//stroke(.45, .23, .78);
	//line(-100, 100, 100, -100);
	for (int i = 0; i < LEN; i++){

		fill(ptCols[i]);
		//noStroke();
		strokeWeight(10); 
		point(ptVecs[i].x, ptVecs[i].y);

		strokeWeight(1);
		if (i>0){
			stroke(.3);
			line(ptVecs[i-1].x, ptVecs[i-1].y, ptVecs[i].x, ptVecs[i].y);
		}

	}

	/*translate(0, 0, 2);
	stroke(.75, .3, .1);
	strokeWeight(3);
	fill(1, .5, .1);
	beginShape(POLYGON);
	for (int i = 0; i < 23; i++){
		vertex(vecs[i].x, vecs[i].y);
	}
	endShape(CLOSE);*/

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