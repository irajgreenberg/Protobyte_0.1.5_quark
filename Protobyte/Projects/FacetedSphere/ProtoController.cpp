#include "ProtoController.h"

void ProtoController::init() {
	light0.setPosition(Vec3(-20, 100, 400));
	globalAmbient = Col3f(.1, .1, .1);
	shadowsOn();
	block = ProtoBlock(Vec3(), Vec3(), Dim3f(330, 330, 330), Col4(.345, .123, 1, 1), "metal_panel01.jpg");
	block.setBumpMap("metal_panel01.jpg");
	block.setTextureScale(Vec2f(.5));
	//Plane.setAmbientMaterial(Col4f(.02, .02, .02, 1.0));
	block.setSpecularMaterial(Col4f(1, 1, 1, 1.0));
	block.setShininess(20);

	float colGap = w / (cols - 1);
	float layGap = d / (lays - 1);
	for (int i = 0; i <= cols; ++i){
		for (int j = 0; j < lays; ++j){
			scl.push_back(Vec3(random(10, 20), random(5, 20), random(10, 30)));
		}
	}


	float theta = PI / 2.0;
	for (int i = 0; i <= cols; ++i){
		float phi = 0.0;

		Vec3 temp = Vec3(cos(theta)*400.0, sin(theta)*400.0, 0.0);

		for (int j = 0; j < lays; ++j){
			pos.push_back(Vec3(sin(phi)*temp.z + cos(phi)*temp.x, temp.y, cos(phi)*temp.z - sin(phi)*temp.x));
			ang.push_back(Vec2(theta, phi));
			phi += TWO_PI / lays;
		}
		theta += PI / cols;
	}
}

void ProtoController::run() {
}

void ProtoController::display() {
	background(1.0, .5, 0);
	//push();
	translate(0, -25, -106);
	arcBallBegin();
	//float colGap = w / (cols - 1);
	//float layGap = d / (lays - 1);
	//for (int i = 0; i < cols; ++i){
	//	for (int j = 0; j < lays; ++j){
	//		int k = i*lays + j;
	//		push();
	//		translate(-w / 2 + colGap*i - hts[k].x / 2, hts[k].y / 2, -d / 2 + layGap*j - hts[k].z/ 2);
	//		scale(hts[k].x, hts[k].y, hts[k].z);
	//		block.display();
	//		pop();
	//	}
	//}




	float theta = PI / 2.0;
	for (int i = 0, k = 0; i <= cols; ++i){
		//push();
		float phi = 0.0;
		for (int j = 0; j < lays; ++j){
			k = i*lays + j;
			push();
			translate(pos.at(k));
			rotate(phi, Vec3(0, 1, 0));
			rotate(theta, Vec3(0, 0, 1));
			scale(scl.at(k).x, scl.at(k).y, scl.at(k).z);
			block.display();
			pop();
			phi += 360.0 / lays;
		}
		//pop();
		theta += 180 / cols;
	}
	arcBallEnd();
	//pop();
}