#include "BrittGeom3.h"

//#define STRIDE ijg::BrittGeom3::STRIDE;

using namespace ijg;

//GLuint BrittGeom3::textureID = 0;

BrittGeom3::BrittGeom3() {


}

BrittGeom3::~BrittGeom3() {


}

void BrittGeom3::clearVectors() {

	
}

void BrittGeom3::init() {
	clearVectors();
	calcVerts();
	calcInds();
	calcFaces();
	calcVertexNorms();
	calcPrimitives();
	//initializeGLEW();
	initializeOpenGL();
}