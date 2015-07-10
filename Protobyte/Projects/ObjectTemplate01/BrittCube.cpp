#include "BrittCube.h"

using namespace ijg;

BrittCube::BrittCube() :
BrittGeom3() {
	println("cube const!");
	clearColor();
	for (int i = 0; i < 8; i++) {
		col4s.push_back(col4);
	}
	init();
}

void BrittCube::calcVerts() {
	Vec3f vs[8];
	vs[0] = Vec3f(-.5, .5, .5);
	vs[1] = Vec3f(-.5, -.5, .5);
	vs[2] = Vec3f(.5, -.5, .5);
	vs[3] = Vec3f(.5, .5, .5);
	vs[4] = Vec3f(.5, .5, -.5);
	vs[5] = Vec3f(.5, -.5, -.5);
	vs[6] = Vec3f(-.5, -.5, -.5);
	vs[7] = Vec3f(-.5, .5, -.5);


	verts.resize(36);
	// FRONT
	verts.at(0) = ProtoVertex3(vs[0], col4s[0], Tup2f(0.0, 0.0));
	verts.at(1) = ProtoVertex3(vs[1], col4s[1], Tup2f(0.0, 1.0 * textureScale.y));
	verts.at(2) = ProtoVertex3(vs[2], col4s[2], Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));

	verts.at(3) = ProtoVertex3(vs[0], col4s[0], Tup2f(0.0, 0.0));
	verts.at(4) = ProtoVertex3(vs[2], col4s[2], Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));
	verts.at(5) = ProtoVertex3(vs[3], col4s[3], Tup2f(1.0 * textureScale.x, 0.0));

	// RIGHT
	verts.at(6) = ProtoVertex3(vs[3], col4s[3], Tup2f(0.0, 0.0));
	verts.at(7) = ProtoVertex3(vs[2], col4s[2], Tup2f(0.0, 1.0 * textureScale.y));
	verts.at(8) = ProtoVertex3(vs[5], col4s[5], Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));

	verts.at(9) = ProtoVertex3(vs[3], col4s[3], Tup2f(0.0, 0.0));
	verts.at(10) = ProtoVertex3(vs[5], col4s[5], Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));
	verts.at(11) = ProtoVertex3(vs[4], col4s[4], Tup2f(1.0 * textureScale.x, 0.0));

	// BACK
	verts.at(12) = ProtoVertex3(vs[4], col4s[4], Tup2f(0.0, 0.0));
	verts.at(13) = ProtoVertex3(vs[5], col4s[5], Tup2f(0.0, 1.0 * textureScale.y));
	verts.at(14) = ProtoVertex3(vs[6], col4s[6], Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));

	verts.at(15) = ProtoVertex3(vs[4], col4s[4], Tup2f(0.0, 0.0));
	verts.at(16) = ProtoVertex3(vs[6], col4s[6], Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));
	verts.at(17) = ProtoVertex3(vs[7], col4s[7], Tup2f(1.0 * textureScale.x, 0.0));

	//LEFT
	verts.at(18) = ProtoVertex3(vs[7], col4s[7], Tup2f(0.0, 0.0));
	verts.at(19) = ProtoVertex3(vs[6], col4s[6], Tup2f(0.0, 1.0 * textureScale.y));
	verts.at(20) = ProtoVertex3(vs[1], col4s[1], Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));

	verts.at(21) = ProtoVertex3(vs[7], col4s[7], Tup2f(0.0, 0.0));
	verts.at(22) = ProtoVertex3(vs[1], col4s[1], Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));
	verts.at(23) = ProtoVertex3(vs[0], col4s[0], Tup2f(1.0 * textureScale.x, 0.0));

	// TOP 
	verts.at(24) = ProtoVertex3(vs[7], col4s[7], Tup2f(0.0, 0.0));
	verts.at(25) = ProtoVertex3(vs[0], col4s[0], Tup2f(0.0, 1.0 * textureScale.y));
	verts.at(26) = ProtoVertex3(vs[3], col4s[3], Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));

	verts.at(27) = ProtoVertex3(vs[7], col4s[7], Tup2f(0.0, 0.0));
	verts.at(28) = ProtoVertex3(vs[3], col4s[3], Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));
	verts.at(29) = ProtoVertex3(vs[4], col4s[4], Tup2f(1.0 * textureScale.x, 0.0));

	//BOTTOM
	verts.at(30) = ProtoVertex3(vs[1], col4s[1], Tup2f(0.0, 0.0));
	verts.at(31) = ProtoVertex3(vs[6], col4s[6], Tup2f(0.0, 1.0 * textureScale.y));
	verts.at(32) = ProtoVertex3(vs[5], col4s[5], Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));

	verts.at(33) = ProtoVertex3(vs[1], col4s[1], Tup2f(0.0, 0.0));
	verts.at(34) = ProtoVertex3(vs[5], col4s[5], Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));
	verts.at(35) = ProtoVertex3(vs[2], col4s[2], Tup2f(1.0 * textureScale.x, 0.0));

}

void BrittCube::calcInds() {
	inds.resize(12);
	for (int i = 0, j = 0; i < inds.size(); i++, j += 3) {
		inds.at(i) = Tup3i(j, j + 1, j + 2);
	}

}