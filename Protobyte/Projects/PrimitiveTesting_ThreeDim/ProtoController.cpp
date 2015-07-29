#include "ProtoController.h"

void ProtoController::init() {
	theta = 0.0;
	clickNum = 0;
	colorsInit();
	//protoBlockInit();
	protoCylInit();
}

void ProtoController::run() {
}

void ProtoController::display() {
	//protoBlockTest(FRAME);
	protoCylTest(FRAME);
	theta += 0.1;
}

// Key and Mouse Events
void ProtoController::keyPressed(){
}

void ProtoController::mousePressed(){
	clickNum++;
	//protoBlockClick();
	protoCylClick();
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

void ProtoController::colorsInit() {
	red = Col4f(1.0, 0.0, 0.0, 1.0);
	blue = Col4f(0.0, 0.0, 1.0, 1.0);
	green = Col4f(0.0, 1.0, 0.0, 1.0);
	magenta = Col4f(1.0, 0.0, 1.0, 1.0);
	yellow = Col4f(1.0, 1.0, 0.0, 1.0);
	cyan = Col4f(0.0, 1.0, 1.0, 1.0);
	black = Col4f(0.0, 0.0, 0.0, 1.0);
	white = Col4f(1.0, 1.0, 1.0, 1.0);
	grey = Col4f(0.5, 0.5, 0.5, 1.0);
}

void ProtoController::setColorsAlpha(float newA) {
	red.setA(newA);
	blue.setA(newA);
	green.setA(newA);
	magenta.setA(newA);
	yellow.setA(newA);
	cyan.setA(newA);
	black.setA(newA);
	white.setA(newA);
	grey.setA(newA);
}

void ProtoController::protoBlockInit() {
	for (int i = 0; i < 5; i++) {
		blocks[i] = ProtoBlock(Vec3f(0, 0, 0), Vec3f(0, 0, 0), Dim3f(10, 10, 10), red);
	}
	blocks[0].setColor(red);
	blocks[1].setColor(blue);
	blocks[2].setColor(green);
	blocks[3].setColor(white);
	blocks[4].setColor(black);
}

void ProtoController::protoBlockTest(TestType type) {
	if (type == COLOR) {
		//Block 0
		push();
		translate(Vec3f(-200, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		blocks[0].display();
		pop();

		//Block 1
		push();
		translate(Vec3f(-100, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		blocks[1].display();
		pop();


		//Block 2
		push();
		translate(Vec3f(0, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		blocks[2].display();
		pop();

		//Block 3
		push();
		translate(Vec3f(100, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		blocks[3].display();
		pop();

		//Block 4
		push();
		translate(Vec3f(200, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		blocks[4].display();
		pop();
	}
	else if (type == FRAME) {
		//Block 0
		push();
		translate(Vec3f(-200, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		blocks[0].display(POINTS, 3);
		pop();

		//Block 1
		push();
		translate(Vec3f(-100, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		blocks[1].display();
		pop();


		//Block 2
		push();
		translate(Vec3f(0, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		blocks[2].display(WIREFRAME, 1);
		pop();

		//Block 3
		push();
		translate(Vec3f(100, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		blocks[3].display();
		pop();

		//Block 4
		push();
		translate(Vec3f(200, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		blocks[4].display(POINTS, 3);
		pop();
	}
}

void ProtoController::protoBlockClick() {
	if (clickNum % 2 == 0) {
		blocks[0].setColor(red);
		blocks[1].setColor(blue);
		blocks[2].setColor(green);
		blocks[3].setColor(white);
		blocks[4].setColor(black);
	}
	else if (clickNum % 2 == 1) {
		blocks[0].setColor(magenta);
		blocks[1].setColor(cyan);
		blocks[2].setColor(yellow);
		blocks[3].setColor(black);
		blocks[4].setColor(white);
	}
}

void ProtoController::protoCylInit() {
	for (int i = 0; i < 5; i++) {
		cyls[i] = ProtoCylinder(50);
	}
	cyls[0].setColor(red);
	cyls[1].setColor(magenta);
	cyls[2].setColor(blue);
	cyls[3].setColor(cyan);
	cyls[4].setColor(green);
}

void ProtoController::protoCylTest(TestType type) {
	if (type == COLOR) {
		//Cylinder 0
		push();
		translate(Vec3f(-200, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		cyls[0].display();
		pop();

		//Cylinder 1
		push();
		translate(Vec3f(-100, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		cyls[1].display();
		pop();


		//Cylinder 2
		push();
		translate(Vec3f(0, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		cyls[2].display();
		pop();

		//Cylinder 3
		push();
		translate(Vec3f(100, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		cyls[3].display();
		pop();

		//Cylinder 4
		push();
		translate(Vec3f(200, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		cyls[4].display();
		pop();
	}
	else if (type == FRAME) {
		//Cylinder 0
		push();
		translate(Vec3f(-200, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		cyls[0].display(POINTS, 3);
		pop();

		//Cylinder 1
		push();
		translate(Vec3f(-100, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		cyls[1].display();
		pop();


		//Cylinder 2
		push();
		translate(Vec3f(0, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		cyls[2].display(WIREFRAME, 1);
		pop();

		//Cylinder 3
		push();
		translate(Vec3f(100, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		cyls[3].display();
		pop();

		//Cylinder 4
		push();
		translate(Vec3f(200, 0, 0));
		scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		cyls[4].display(POINTS, 3);
		pop();
	}
}

void ProtoController::protoCylClick() {
	if (clickNum % 2 == 0) {
		cyls[0].setColor(red);
		cyls[1].setColor(magenta);
		cyls[2].setColor(blue);
		cyls[3].setColor(cyan);
		cyls[4].setColor(green);
	}
	else if (clickNum % 2 == 1) {
		cyls[0].setColor(black);
		cyls[1].setColor(grey);
		cyls[2].setColor(white);
		cyls[3].setColor(grey);
		cyls[4].setColor(black);
	}
}