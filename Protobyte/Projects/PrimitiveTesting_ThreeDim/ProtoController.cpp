#include "ProtoController.h"

void ProtoController::init() {
	theta = 0.0;
	clickNum = 0;
	colorsInit();
	//protoBlockInit(BRITT);
	protoCylInit(BRITT);
	//protoSphereInit();
	//protoTorInit();

	block = ProtoBlock(Vec3f(0, 0, 0), Vec3f(0, 0, 0), Dim3f(1, 1, 1), blue);
	cylinder = ProtoCylinder(Vec3f(0, 0, 0), Dim3f(1, 1, 1), 20);
	cylinder.setColor(red);
	sphere = ProtoSphere(Vec3f(0, 0, 0), Vec3f(0, 0, 0), Dim3f(300, 300, 1), magenta, 25, 25);
	toroid = ProtoToroid(Vec3f(0, 0, 0), Vec3f(0, 0, 0), Dim3f(1, 1, 1), black, 20, 20, 75, 25);
}

void ProtoController::run() {
}

void ProtoController::display() {
	//protoBlockTest();
	protoCylTest();
	//protoSphereTest(FRAME);
	//protoTorTest(FRAME);
	//blockTest();
	//cylinderTest(FRAME);
	//sphereTest(PNTS);
	//toroidTest(FRAME);
	theta += 0.1;
}

// Key and Mouse Events
void ProtoController::keyPressed(){
}

void ProtoController::mousePressed(){
	clickNum++;
	//protoBlockClick();
	protoCylClick();
	//protoSphereClick();
	//protoTorClick();
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

void ProtoController::protoBlockInit(ConstType type) {
	switch (type)
	{
	case ProtoController::PROTO:
		for (int i = 0; i < 5; i++) {
			blocks[i] = ProtoBlock(Vec3f(0, 0, 0), Vec3f(0, 0, 0), Dim3f(10, 10, 10), red);
		}
		blocks[0].setColor(red);
		blocks[1].setColor(blue);
		blocks[2].setColor(green);
		blocks[3].setColor(white);
		blocks[4].setColor(black);
		print("Using proto constructors.");
		break;
	case ProtoController::BRITT:
		blocks[0] = Block(red);
		blocks[1] = Block(blue);
		blocks[2] = Block(green);
		blocks[3] = Block(white);
		blocks[4] = Block(black);
		print("Using brittni's constructors.");
		break;
	default:
		break;
	}

	
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

void ProtoController::protoCylInit(ConstType type) {
	switch (type)
	{
	case ProtoController::PROTO:
		for (int i = 0; i < 5; i++) {
			cyls[i] = ProtoCylinder(50);
		}
		cyls[0].setColor(red);
		cyls[1].setColor(magenta);
		cyls[2].setColor(blue);
		cyls[3].setColor(cyan);
		cyls[4].setColor(green);
		print("Using proto constructors.");
		break;
	case ProtoController::BRITT:
		cyls[0] = Cylinder(red);
		cyls[1] = Cylinder(magenta);
		cyls[2] = Cylinder(blue);
		cyls[3] = Cylinder(cyan);
		cyls[4] = Cylinder(green);
		print("Using brittni's constructors.");
		break;
	default:
		break;
	} 
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

void ProtoController::protoSphereInit() {
	for (int i = 0; i < 5; i++) {
		spheres[i] = ProtoSphere(Vec3f(0, 0, 0), Vec3f(0, 0, 0), Dim3f(75, 75, 75), red, 20, 20);
	}
	spheres[0].setColor(blue);
	spheres[1].setColor(grey);
	spheres[2].setColor(cyan);
	spheres[3].setColor(grey);
	spheres[4].setColor(green);
}

void ProtoController::protoSphereTest(TestType type) {
	if (type == COLOR) {
		//Sphere 0
		push();
		translate(Vec3f(-200, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		spheres[0].display();
		pop();

		//Sphere 1
		push();
		translate(Vec3f(-100, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		spheres[1].display();
		pop();


		//Sphere 2
		push();
		translate(Vec3f(0, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		spheres[2].display();
		pop();

		//Sphere 3
		push();
		translate(Vec3f(100, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		spheres[3].display();
		pop();

		//Sphere 4
		push();
		translate(Vec3f(200, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		spheres[4].display();
		pop();
	}
	else if (type == FRAME) {
		//Sphere 0
		push();
		translate(Vec3f(-200, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		spheres[0].display(POINTS, 3);
		pop();

		//Sphere 1
		push();
		translate(Vec3f(-100, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		spheres[1].display();
		pop();


		//Sphere 2
		push();
		translate(Vec3f(0, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		spheres[2].display(WIREFRAME, 1);
		pop();

		//Sphere 3
		push();
		translate(Vec3f(100, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		spheres[3].display();
		pop();

		//Sphere 4
		push();
		translate(Vec3f(200, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		spheres[4].display(POINTS, 3);
		pop();
	}
}

void ProtoController::protoSphereClick() {
	if (clickNum % 2 == 0) {
		spheres[0].setColor(blue);
		spheres[1].setColor(grey);
		spheres[2].setColor(cyan);
		spheres[3].setColor(grey);
		spheres[4].setColor(green);
	}
	else if (clickNum % 2 == 1) {
		spheres[0].setColor(black);
		spheres[1].setColor(red);
		spheres[2].setColor(black);
		spheres[3].setColor(magenta);
		spheres[4].setColor(black);
	}
}

void ProtoController::protoTorInit() {
	for (int i = 0; i < 5; i++) {
		tors[i] = ProtoToroid(Vec3f(0, 0, 0), Vec3f(0, 0, 0), Dim3f(10, 10, 10), red, 20, 15, 75, 20);
	}
	tors[0].setColor(green);
	tors[1].setColor(black);
	tors[2].setColor(yellow);
	tors[3].setColor(black);
	tors[4].setColor(red);
}

void ProtoController::protoTorTest(TestType type) {
	if (type == COLOR) {
		//Toroid 0
		push();
		translate(Vec3f(-200, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		tors[0].display();
		pop();

		//Toroid 1
		push();
		translate(Vec3f(-100, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		tors[1].display();
		pop();


		//Toroid 2
		push();
		translate(Vec3f(0, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		tors[2].display();
		pop();

		//Toroid 3
		push();
		translate(Vec3f(100, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		tors[3].display();
		pop();

		//Toroid 4
		push();
		translate(Vec3f(200, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		tors[4].display();
		pop();
	}
	else if (type == FRAME) {
		//Toroid 0
		push();
		translate(Vec3f(-200, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		tors[0].display(POINTS, 3);
		pop();

		//Toroid 1
		push();
		translate(Vec3f(-100, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		tors[1].display();
		pop();


		//Toroid 2
		push();
		translate(Vec3f(0, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		tors[2].display(WIREFRAME, 1);
		pop();

		//Toroid 3
		push();
		translate(Vec3f(100, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		tors[3].display();
		pop();

		//Toroid 4
		push();
		translate(Vec3f(200, 0, 0));
		//scale(75);
		rotate(theta, Vec3f(0.5, 0.5, 0.0));
		tors[4].display(POINTS, 3);
		pop();
	}
}

void ProtoController::protoTorClick() {
	if (clickNum % 2 == 0) {
		tors[0].setColor(green);
		tors[1].setColor(black);
		tors[2].setColor(yellow);
		tors[3].setColor(black);
		tors[4].setColor(red);
	}
	else if (clickNum % 2 == 1) {
		tors[0].setColor(black);
		tors[1].setColor(cyan);
		tors[2].setColor(white);
		tors[3].setColor(cyan);
		tors[4].setColor(black);
	}
}

void ProtoController::blockTest(TestType test) {
	if (test == COLOR) {
		push();
		scale(100);
		rotate(theta, Vec3f(0.4, 0.3, 0.3));
		block.display();
		pop();
	}
	else if (test == FRAME) {
		push();
		scale(100);
		rotate(theta, Vec3f(0.4, 0.3, 0.3));
		block.display(WIREFRAME, 1);
		pop();
	}
	else if (test = PNTS) {
		push();
		scale(100);
		rotate(theta, Vec3f(0.4, 0.3, 0.3));
		block.display(POINTS, 3);
		pop();
	}
}

void ProtoController::cylinderTest(TestType type) {
	switch (type)
	{
	case ProtoController::COLOR:
		push();
		scale(100);
		rotate(theta, Vec3f(0.4, 0.3, 0.3));
		cylinder.display();
		pop();
		break;
	case ProtoController::FRAME:
		push();
		scale(100);
		rotate(theta, Vec3f(0.4, 0.3, 0.3));
		cylinder.display(WIREFRAME, 1);
		pop();
		break;
	case ProtoController::PNTS:
		push();
		scale(100);
		rotate(theta, Vec3f(0.4, 0.3, 0.3));
		cylinder.display(POINTS, 3);
		pop();
		break;
	default:
		break;
	}
}

void ProtoController::sphereTest(TestType type) {
	switch (type)
	{
	case ProtoController::COLOR:
		push();
		rotate(theta, Vec3f(0.4, 0.3, 0.3));
		sphere.display();
		pop();
		break;
	case ProtoController::FRAME:
		push();
		rotate(theta, Vec3f(0.4, 0.3, 0.3));
		sphere.display(WIREFRAME, 1);
		pop();
		break;
	case ProtoController::PNTS:
		push();
		rotate(theta, Vec3f(0.4, 0.3, 0.3));
		sphere.display(POINTS, 3);
		pop();
		break;
	default:
		break;
	}
}

void ProtoController::toroidTest(TestType type) {
	switch (type)
	{
	case ProtoController::COLOR:
		push();
		rotate(theta, Vec3f(0.4, 0.3, 0.3));
		toroid.display();
		pop();
		break;
	case ProtoController::FRAME:
		push();
		rotate(theta, Vec3f(0.4, 0.3, 0.3));
		toroid.display(WIREFRAME, 1);
		pop();
		break;
	case ProtoController::PNTS:
		push();
		rotate(theta, Vec3f(0.4, 0.3, 0.3));
		toroid.display(POINTS, 3);
		pop();
		break;
	default:
		break;
	}
}