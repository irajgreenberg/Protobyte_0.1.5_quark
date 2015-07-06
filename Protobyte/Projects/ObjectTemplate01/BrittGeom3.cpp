#include "BrittGeom3.h"

//#define STRIDE ijg::BrittGeom3::STRIDE;

using namespace ijg;

//GLuint BrittGeom3::textureID = 0;

BrittGeom3::BrittGeom3():
diffuseMapImage("white_tile.jpg"), textureScale(Vec2f(1, 1)) {
	println("in geom constructor.");
}

BrittGeom3::~BrittGeom3() {
#ifdef FREEIMAGE_LIB
	FreeImage_DeInitialize();
#endif
}

void BrittGeom3::clearVectors() {
	if (verts.size() > 0) {
		verts.clear();
	}
	if (inds.size() > 0) {
		inds.clear();
	}
	if (color.size() > 0) {
		color.clear();
	}
	if (indPrims.size() > 0) {
		indPrims.clear();
	}
	if (interleavedPrims.size() > 0) {
		interleavedPrims.clear();
	}
	if (geomSets.size() > 0) {
		geomSets.clear();
	}
}

void BrittGeom3::init() {
	clearVectors();
	createDiffuseMapTexture(diffuseMapImage);
	calcVerts();
	calcInds();
	//calcFaces();
	//calcVertexNorms();
	//calcPrimitives();
	//initializeGLEW();
	//initializeOpenGL();
}

void BrittGeom3::createDiffuseMapTexture(const std::string& diffuseMapImage) {
	diffuseMapTexture = ProtoTexture(diffuseMapImage, ProtoTexture::DIFFUSE_MAP, GL_RGB, GL_RGB, 0, 0);
	diffuseMapLoc = glGetUniformLocation(ProtoShader::getID_2(), "diffuseMap");
	glUniform1i(diffuseMapLoc, 0);
}