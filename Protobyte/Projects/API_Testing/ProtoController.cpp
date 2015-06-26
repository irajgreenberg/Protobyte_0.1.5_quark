#include "ProtoController.h"

void ProtoController::init() {
	setBackground(0.7);
	x = -(getWidth() / 2);
	y = 0;
	x1 = 0;
	y1 = getHeight() / 2;
	topCornerX = x;
	topCornerY = getHeight() / 2;
	theta = 0.0;

	pos = Vec3(100, -200, 0);
	rot = Vec3(30, 0, 45);
	size = Dim2f(100, 100);
	color = Col4f(0.0, 0.0, 1.0, 1.0);
	detail = 5;

	colors.push_back(red);
	colors.push_back(yellow);
	colors.push_back(green);
	colors.push_back(cyan);
	colors.push_back(blue);
	colors.push_back(pink);
	colors.push_back(red);
	colors.push_back(black);

	e0 = ProtoEllipse(pos, rot, size, red, detail);
	b0 = ProtoBlock(pos, rot, size, color);
	b1 = ProtoBlock(pos, rot, size, red);
	t0 = Toroid(pos, rot, size, color, 20, 20, 100, 40);

	for (int i = 0; i < 5; i++) {
		blocks[i] = ProtoBlock(pos, rot, size, colors);
	}
}

void ProtoController::run() {
}

void ProtoController::display() {
	protoBlockTest();
	//edgeTesting();
}

void ProtoController::mousePressed() {
	std::cout << "mouseX = " << mouseX << std::endl;
	std::cout << "mouseY = " << mouseY << std::endl;
	std::cout << "frameCount = " << getFrameCount() << std::endl;
	clickCount++;
	if (clickCount % 2 == 0) {
		b1.setColor(red);
	}
	else {
		b1.setColor(black);
	}
}

void ProtoController::edgeTesting() {
	noStroke();
	fill(blue);
	ellipse(x, y, 20, 20);
	if (x <= -(getWidth() / 2)) {
		xSpeed = 1;
	}
	else if (x >= (getWidth() / 2)) {
		xSpeed = -1;
	}
	x += xSpeed;

	fill(red);
	ellipse(x1, y1, 20, 20);
	if (y1 <= -(getHeight() / 2)) {
		ySpeed = 1;
	}
	else if (y1 >= (getHeight() / 2)) {
		ySpeed = -1;
	}
	y1 += ySpeed;

	stroke(black);
	strokeWeight(1);
	fill(red);
	rect(topCornerX, topCornerY, 25, 25);

	fill(black);
	rect(topCornerX, topCornerY, 1, getHeight());
	rect(topCornerX, topCornerY, getWidth(), 1);
}

void ProtoController::centerShapes() {
	noFill();
	strokeWeight(1);
	stroke(black);
	rect(0, 0, 200, 200, CENTER);

	stroke(0.5, 0.1, 0.4);
	strokeWeight(3);
	fill(0.2, 0.5, 0.3);
	ellipse(0, 0, 100, 100);
}

void ProtoController::matrixTesting() {
	push();
	rotate(theta, 0.0, 0.0, 1.0);
	centerShapes();
	pop();
	noFill();
	rect(0, 0, 100, 100, CENTER);
	rect(100 * sqrt(2), 0, 50, 50);
	push();
	translate(300, 0, 0);
	rect(0, 0, 100, 100, CENTER);
	pop();
	fill(blue);
	ellipse(300, 0, 50, 50);
	theta += 1.0;
}

void ProtoController::scaleTesting() {
	push();
	scale(40);
	stroke(black);
	fill(red);
	rect(0, 0, 5, 5, CENTER);
	pop();
}

void ProtoController::spinnySquare() {
	arcBallBegin();
	scaleTesting();
	arcBallEnd();
}

void ProtoController::rectTestA() {
	translate(400, 0, 0);
	stroke(black);
	fill(0.5, 0.1, 0.4);
	rect(100, 200, CORNER_TR);
	noFill();
	rect(100, 200);
	rect(100, 200, CORNER);
	rect(100, 200, CORNER_BL);
	rect(100, 200, CORNER_BR);
}

void ProtoController::rectTestB() {
	fill(white);
	rect(0, 0, 100, 100);
	noFill();
	rect(0, 0, 100, 100, CENTER);
	rect(0, 0, 100, 100, CORNER_BR);
	rect(0, 0, 100, 100, CORNER_TR);
	rect(0, 0, 100, 100, CORNER_BL);
	rect(100, 100, 100, 200, CORNER_BL);
}

void ProtoController::rectTestC() {
	stroke(black);
	strokeWeight(1);

	Vec2 a1 = Vec2(0, 0);
	Vec2 a2 = Vec2(200, -200);
	Vec2 b1 = Vec2(0, 200);
	Vec2 b2 = Vec2(200, 0);
	Vec2 c1 = Vec2(-200, 200);
	Vec2 c2 = Vec2(0, 0);
	Vec2 d1 = Vec2(-200, 0);
	Vec2 d2 = Vec2(0, -200);

	fill(red);
	rect(a1, a2);

	fill(blue);
	rect(b1, b2);

	fill(green);
	rect(c1, c2);

	fill(white);
	rect(d1, d2);

	fill(black);
	rect(Vec2(200, 200), Vec2(300, 100));
	rect(Vec2(200, -100), Vec2(300, -200));
	rect(Vec2(-300, 200), Vec2(-200, 100));
	rect(Vec2(-300, -100), Vec2(-200, -200));

	fill(pink);
	rect(Vec2(200, 100), Vec2(300, -100));
	rect(Vec2(-300, -200), Vec2(300, -300));
	rect(Vec2(-300, 300), Vec2(300, 200));
	rect(Vec2(-300, 100), Vec2(-200, -100));

	noFill();
	strokeWeight(4);
	rect(Vec2(-400, 400), Vec2(400, -400));

	noFill();
	strokeWeight(1);
	ellipse(0, 0, 10, 10);
	ellipse(200, 200, 10, 10);
	ellipse(200, -200, 10, 10);
	ellipse(-200, -200, 10, 10);
	ellipse(-200, 200, 10, 10);
	ellipse(0, 200, 10, 10);
	ellipse(0, -200, 10, 10);
	ellipse(-200, 0, 10, 10);
	ellipse(200, 0, 10, 10);
}

void ProtoController::rectTestD() {
	stroke(black);
	strokeWeight(1);

	fill(white);
	rect(Vec2(0, 0), Vec2(100, -100));

	noFill();
	rect(Vec2(0, 0), Vec2(100, -100), CENTER);
	rect(Vec2(0, 0), Vec2(100, -100), CORNER_BL);
	rect(Vec2(0, 0), Vec2(100, -100), CORNER_BR);
	rect(Vec2(0, 0), Vec2(100, -100), CORNER_TR);

	noFill();
	ellipse(0, 0, 10, 10);
	ellipse(100, 100, 10, 10);
	ellipse(100, -100, 10, 10);
	ellipse(-100, -100, 10, 10);
	ellipse(-100, 100, 10, 10);
}

void ProtoController::ellipseTestA() {
	blue.a = 0.5;
	fill(blue);
	ellipse(0, 0, 50, 50);
	ellipse(0, 0, 50, 50, CORNER);
	ellipse(0, 0, 50, 50, CORNER_TR);
	ellipse(0, 0, 50, 50, CORNER_BR);
	ellipse(0, 0, 50, 50, CORNER_BL);
	noFill();
	rect(0, 0, 50, 50);
	rect(-50, -50, 50, 100, CENTER);
	red.setA(0.5);
	fill(red);
	ellipse(50, 50, 50, 50);
	ellipse(-50, 50, 50, 50);
	ellipse(-50, -50, 50, 100);
	ellipse(50, -50, 50, 100);
}

void ProtoController::ellipseTestB() {
	blue.setA(0.5);
	green.setA(0.5);

	fill(blue);
	ellipse(0, 0, 100);
	ellipse(0, 0, 100, CORNER);
	ellipse(0, 0, 100, CORNER_BL);
	ellipse(0, 0, 100, CORNER_BR);
	ellipse(0, 0, 100, CORNER_TR);

	ellipse(300, 400, 67);

	noFill();
	rect(100, 100);
	rect(300, 400, 67, 67, CENTER);
}

void ProtoController::ellipseTestC() {
	green.setA(0.5);
	blue.setA(0.5);

	fill(green);
	ellipse(100);
	ellipse(100, CORNER);
	ellipse(100, CORNER_TR);
	ellipse(100, CORNER_BL);
	ellipse(100, CORNER_BR);

	noFill();
	rect(100, 100);

	push();
	translate(300, 200, 0);
	fill(blue);
	ellipse(200);
	pop();

	noFill();
	rect(300, 200, 200, 200, CENTER);
}

void ProtoController::ellipseTestD() {
	red.setA(0.5);
	green.setA(0.5);

	fill(red);
	ellipse(136, 289);

	fill(green);
	ellipse(136, 289, CORNER);
	ellipse(136, 289, CORNER_TR);
	ellipse(136, 289, CORNER_BR);
	ellipse(136, 289, CORNER_BL);

	push();
	translate(-200, 400, 0);
	fill(red);
	ellipse(235, 192);
	pop();

	noFill();
	rect(136, 289, CENTER);
	rect(-200, 400, 235, 192, CENTER);
}

void ProtoController::quadTestA() {
	blue.setA(0.5);
	fill(blue);
	//quad(-100, 100, -100, -100, 100, -100, 100, 100, CORNER);

	red.setA(0.5);
	strokeWeight(1);
	fill(red);

	push();
	translate(300, 0, 0);
	pink.setA(0.5);
	fill(pink);
	quad(0, 100, -100, 0, 0, -100, 100, 0, CORNER);
	pop();

	push();
	translate(300, 0, 0);
	rotate(45, 0, 0, 1.0);
	green.setA(0.5);
	fill(green);
	quad(0, 100, -100, 0, 0, -100, 100, 0, CORNER);
	pop();

	push();
	translate(300, 0, 0);
	rotate(45 / 2, 0, 0, 1.0);
	fill(blue);
	quad(0, 100, -100, 0, 0, -100, 100, 0, CORNER);
	pop();

	push();
	translate(300, 0, 0);
	rotate(-(45 / 2), 0, 0, 1.0);
	fill(red);
	quad(0, 100, -100, 0, 0, -100, 100, 0, CORNER);
	pop();

	//quad(-100, 100, 0, 0, 100, -100, 100, 100, CORNER);

	fill(red);
	quad(0, 200, -200, 0, 0, 100, 200, 0, CORNER);

	fill(blue);
	quad(-300, 200, -400, 100, -100, 100, -200, 200, CORNER);

	noFill();
	ellipse(10);
	ellipse(0, 100, 10);
	ellipse(0, 200, 10);
	ellipse(-300, 200, 10);
	ellipse(-100, 100, 10);

	green.setA(0.5);
	fill(green);
	//ellipse(-100, -100, 10);
}

void ProtoController::quadTestB() {
	Vec2 a = Vec2(0, 200);
	Vec2 b = Vec2(100, 100);
	Vec2 c = Vec2(0, -100);
	Vec2 d = Vec2(-100, 100);

	red.a = 0.5;
	fill(red);

	push();
	rotate(180, 0, 0, 1.0);
	//quad(a, b, c, d);
	quad(a, b, c, d, CORNER);
	pop();

	quad(a, b, c, d, CORNER);

	blue.setA(0.5);

	a = Vec2(-200, 100);
	b = Vec2(0, 100);
	c = Vec2(-50, 0);
	d = Vec2(-250, 0);

	fill(blue);
	quad(a, b, c, d, CORNER);

	push();

	noFill();

	ellipse(0, 200, 10);
	ellipse(0, -200, 10);
}

void ProtoController::pixelTesting() {
	fill(blue);
	rect(100, 200);
}

void ProtoController::protoEllipseTest() {
	push();
	scale(100, 100, 100);
	e0.display();
	pop();
	noFill();
	ellipse(100, 100, 10);
	ellipse(400, 0, 10);
	ellipse(550, 0, 10);
	rect(200, 200);
	rect(100, 400, 50, 50, CENTER);

	blue.setA(0.5);
	fill(blue);
	ellipseDetail = 5;
	ellipse(400, 0, 300);
}

void ProtoController::viewTest() {
	fill(red);
	rect(100, 100, 100, 100, CENTER);

	push();
	translate(0, 0, -500);
	//rotate(45, 0.0, 0.0, 1.0);
	fill(blue);
	rect(100, 100, CENTER);
	pop();

	push();
	translate(-100, -100, 0);
	fill(pink);
	rect(100, 100);
	pop();

	push();
	translate(50, 100, -550);
	fill(green);
	rect(200, 200);
	pop();

	push();
	translate(-50, -100, -400);
	fill(black);
	rect(200, 200);
	pop();
}

void ProtoController::protoBlockTest() {
	//blocks[0].setColor(green);
	//blocks[1].setColor(yellow);
	//blocks[2].setColor(red);
	//blocks[3].setColor(pink);
	//blocks[4].setColor(blue);

	for (int i = 0; i < 5; i++) {
		push();
		translate(-100, 200 - (100 * i), 0);
		if (i == 3) {
			rotate(theta * 2, 0.0, 1.0, 0.0);
		}
		else if (i % 2 == 1) {
			rotate(-theta, 0.0, 1.0, 0.0);
		}
		else {
			rotate(theta, 0.0, 1.0, 0.0);
		}
		scale(100, 100, 100);
		blocks[i].display();
		pop();
	}

	push();
	translate(100, -200, 0);
	rotate(-theta, 0.0, 1.0, 0.0);
	scale(100, 100, 100);
	b0.display(WIREFRAME);
	pop();

	push();
	translate(100, -100, 0);
	rotate(theta, 0.0, 1.0, 0.0);
	scale(100, 100, 100);
	b1.display();
	pop();

	push();
	translate(-400, 0, 0);
	rotate(90, 1.0, 0.0, 0.0);
	rotate(theta, 0.0, 0.0, 1.0);
	t0.display(POINTS, 6);
	pop();

	theta += 0.5;
}