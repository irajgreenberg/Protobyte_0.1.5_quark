/*!  \brief  ProtoCylinder.cpp: (add brief description)
 ProtoCylinder.cpp
 Protobyte Library v02

 Created by Ira on 12/23/13.
 Copyright (c) 2013 Ira Greenberg. All rights reserved.

 Library Usage:
 This work is licensed under the Creative Commons
 Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 To view a copy of this license, visit
 http://creativecommons.org/licenses/by-nc-sa/3.0/
 or send a letter to Creative Commons,
 444 Castro Street, Suite 900,
 Mountain View, California, 94041, USA.

 This notice must be retained any source distribution.

 \ingroup common
 This class is part of the group common (update)
 \sa NO LINK
 */

#include "ProtoCylinder.h"

using namespace ijg;

// default cstr
ProtoCylinder::ProtoCylinder() :
ProtoGeom3(Vec3f(), Vec3f(), Dim3f(1), Col4f(1),
	"white_tile.jpg", Vec2(1)), detail(12), registration(CENTER),
	ellipseWidth(1.0), ellipseHeight(1.0),
	length(1.0) {
	//init();
}

//overloaded cstr's
ProtoCylinder::ProtoCylinder(int detail, Registration reg) :
ProtoGeom3(Vec3f(), Vec3f(), Dim3f(1), Col4f(1),
	"white_tile.jpg", Vec2(1)), detail(detail), registration(reg),
	ellipseWidth(1.0), ellipseHeight(1.0),
	length(1.0) {
	//setBumpMap("white_tile.jpg");
	init();
}

ProtoCylinder::ProtoCylinder(const Vec3& pos, int detail, Registration reg) :
ProtoGeom3(pos, Vec3f(), Dim3f(1), Col4f(1), "white_tile.jpg",
	Vec2(1)), detail(detail), registration(reg), 
	ellipseWidth(1.0), ellipseHeight(1.0), 
	length(1.0) {
	init();
}

ProtoCylinder::ProtoCylinder(const Dim3f& size, int detail, Registration reg) :
ProtoGeom3(Vec3f(), Vec3f(), size, Col4f(1), "white_tile.jpg",
	Vec2(1)), detail(detail), registration(reg),
	ellipseWidth(1.0), ellipseHeight(1.0),
	length(1.0) {
	init();
}

ProtoCylinder::ProtoCylinder(const Vec3& pos, const Dim3f& size, int detail, Registration reg) :
ProtoGeom3(pos, Vec3f(), size, Col4f(1), "white_tile.jpg",
	Vec2(1)), detail(detail), registration(reg), 
	ellipseWidth(1.0), ellipseHeight(1.0), 
	length(1.0) {
	init();
}

ProtoCylinder::ProtoCylinder(int detail, const std::string& textureImageURL, Registration reg) :
ProtoGeom3(Vec3f(), Vec3f(), Dim3f(1), Col4f(1), textureImageURL,
	Vec2(1)), detail(detail), registration(reg), 
	ellipseWidth(1.0), ellipseHeight(1.0), 
	length(1.0) {
	init();
}

ProtoCylinder::ProtoCylinder(const Vec3& pos, int detail, const std::string& textureImageURL, Registration reg) :
ProtoGeom3(pos, Vec3f(), Dim3f(1), Col4f(1), textureImageURL,
	Vec2(1)), detail(detail), registration(reg), 
	ellipseWidth(1.0), ellipseHeight(1.0), 
	length(1.0) {
	init();
}

ProtoCylinder::ProtoCylinder(const Dim3f& size, int detail, const std::string& textureImageURL, Registration reg) :
ProtoGeom3(Vec3f(), Vec3f(), size, Col4f(1), textureImageURL,
	Vec2(1)), detail(detail), registration(reg), 
	ellipseWidth(1.0), ellipseHeight(1.0),
	length(1.0) {
	init();
}

ProtoCylinder::ProtoCylinder(const Vec3& pos, const Dim3f& size, int detail, const std::string& textureImageURL, Registration reg) :
ProtoGeom3(pos, Vec3f(), size, Col4f(1), textureImageURL,
	Vec2(1)), detail(detail), registration(reg),
	ellipseWidth(1.0), ellipseHeight(1.0),
	length(1.0) {
	init();
}

//new constructors - bw
ProtoCylinder::ProtoCylinder(const Col4f& col4):
ProtoGeom3(col4), detail(20), registration(CENTER),
	ellipseWidth(1.0), ellipseHeight(1.0),
	length(1.0) {
	init();
}

ProtoCylinder::ProtoCylinder(float ellipseWidth, float ellipseHeight, float length, const Col4f& col4) :
ProtoGeom3(col4), registration(CENTER), detail(20),
ellipseWidth(ellipseWidth), ellipseHeight(ellipseHeight),
length(length) {
	init();
}

ProtoCylinder::ProtoCylinder(const Dim3f& dims, const Col4f& col4) :
ProtoGeom3(col4), registration(CENTER), detail(20),
ellipseWidth(dims.w), ellipseHeight(dims.h), length(dims.d) {
	init();
}

//ProtoCylinder::ProtoCylinder(float ellipseWidth, float ellipseHeight, float length, int detail, const Col4f& col4):
//ProtoGeom3(col4), registration(CENTER), detail(detail),
//	ellipseWidth(ellipseWidth), ellipseHeight(ellipseHeight),
//	length(length) {
//	init();
//}

//ProtoCylinder::ProtoCylinder(const Dim3f& dims, int detail, const Col4f& col4) :
//ProtoGeom3(col4), registration(CENTER), detail(detail),
//ellipseWidth(dims.w), ellipseHeight(dims.h), length(dims.d) {
//	init();
//}

void ProtoCylinder::calcVerts() {
	//trace(verts.size());

	// pack terminals up front in 0, 1 positions

	float theta = 0;
	float x = 0;
	float y = 0;
	float z = 0;
	switch (registration) {
	case LEFT:
		// terminals
		verts.push_back(ProtoVertex3(Vec3f(0, 0, 0),
			ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0, 0)));
		verts.push_back(ProtoVertex3(Vec3f(0, size.h, 0),
			ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0, 1.0 / size.h)));
		for (int i = 0; i < detail; ++i){
			z = cos(theta)*size.d;
			x = sin(theta)*size.w;
			verts.push_back(ProtoVertex3(Vec3f(x, y, z),
				ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(x / size.w, y / size.h)));

			verts.push_back(ProtoVertex3(Vec3f(x, size.h, z),
				ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(x / size.w, y / size.h)));
			theta += TWO_PI / detail;
		}
		break;
	case CENTER:
		for (int i = 0; i < 2; ++i){
			theta = 0;
			for (int j = 0; j < detail; ++j){
				y = cos(theta) * ellipseHeight;
				z = sin(theta) * ellipseWidth;
				//verts.push_back(ProtoVertex3(Vec3f(-.5 + (1 * i), y, z),
				//	ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(theta / TWO_PI, (i*detail + j) / (detail * 2.0f))));
				//removed trace - bw
				//trace(theta / TWO_PI);
			//verts.push_back(ProtoVertex3(Vec3f(-.5 + (1 * i), y, z),
			//	ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(theta / TWO_PI, -.5 + (i*i))));
			//		theta += TWO_PI / (detail-1);

					verts.push_back(ProtoVertex3(Vec3f((-.5 * length) + (length * i), y, z),
						ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(theta / TWO_PI, -.5 + (i*i))));
					theta += TWO_PI / (detail - 1);
			}
		}
		verts.push_back(ProtoVertex3(Vec3f(-.5 * length, 0, 0),
			ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(-.5, 0)));
		verts.push_back(ProtoVertex3(Vec3f(.5 * length, 0, 0),
			ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(.5, 0)));
		break;
	case RIGHT:
		//terminals
		verts.push_back(ProtoVertex3(Vec3f(0, 0, 0),
			ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0, 0)));
		verts.push_back(ProtoVertex3(Vec3f(-size.w, 0, 0),
			ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(1.0 / -size.w, 0)));
		for (int i = 0; i < detail; ++i){
			y = cos(theta)*size.h;
			z = sin(theta)*size.d;
			verts.push_back(ProtoVertex3(Vec3f(0, y, z),
				ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(x, y / size.h)));

			verts.push_back(ProtoVertex3(Vec3f(-size.w, y, z),
				ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(x / -size.w, y / size.h)));
			theta += TWO_PI / detail;
		}

		break;

	default:
		break;
	}

}


void ProtoCylinder::calcInds() {
	int len = detail;
	for (int i = 0; i < detail; ++i) {
		if (i<detail-1){
			// left cap
			inds.push_back(ProtoTuple3i(i, verts.size()-2, i+1)); // change
			// right cap
			inds.push_back(ProtoTuple3i(i + len + 1, verts.size() - 1, i + len)); 
			// body
			inds.push_back(ProtoTuple3i(i+1, i + len, i));
			inds.push_back(ProtoTuple3i(i + len + 1, i + len, i + 1));
		}
		else { // close cylinder
			// left cap
			//inds.push_back(ProtoTuple3i(i, verts.size() - 2, 0));
			//// right cap
			//inds.push_back(ProtoTuple3i(len, verts.size() - 1, i+len));
			//// body
			//inds.push_back(ProtoTuple3i(0, i + len, i));
			//inds.push_back(ProtoTuple3i(len, i + len, 0));
		}

	}
}
