#include "BrittGeom3.h"

//#define STRIDE ijg::BrittGeom3::STRIDE;

using namespace ijg;

//GLuint BrittGeom3::textureID = 0;

BrittGeom3::BrittGeom3():
diffuseMapImage("white_tile.jpg"), textureScale(Vec2f(1, 1)) { //moved texture scale set to Geom constructor
	println("in geom constructor.");
}

BrittGeom3::~BrittGeom3() {
#ifdef FREEIMAGE_LIB
	FreeImage_DeInitialize();
#endif
}

void BrittGeom3::clearVectors() {
	//removed unnecessary vectors and clearing
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
	if (faces.size() > 0) {
		faces.clear();
	}
}

void BrittGeom3::init() {
	clearVectors();
	createDiffuseMapTexture(diffuseMapImage);
	calcVerts();
	calcInds();
	calcFaces();
	calcVertexNorms();
	calcPrimitives();

	//necessary?
	materials = Material();

	setMaterialMemLocs();

	//initializeGLEW();
	//initializeOpenGL();
}

void BrittGeom3::createDiffuseMapTexture(const std::string& diffuseMapImage) {
	diffuseMapTexture = ProtoTexture(diffuseMapImage, ProtoTexture::DIFFUSE_MAP, GL_RGB, GL_RGB, 0, 0);
	diffuseMapLoc = glGetUniformLocation(ProtoShader::getID_2(), "diffuseMap");
	glUniform1i(diffuseMapLoc, 0);
}

void BrittGeom3::calcFaces() {
	if (faces.size() > 0) {
		faces.clear();
	}
	for (int i = 0; i < inds.size(); i++) {
		faces.push_back(ProtoFace3(&verts.at(inds.at(i).elem0), &verts.at(inds.at(i).elem1),
			&verts.at(inds.at(i).elem2)));
	}
}

void BrittGeom3::calcVertexNorms() {
	if (geomSets.size()>0){
		geomSets.clear();
	}

	for (int i = 0; i < verts.size(); i++) {
		Vec3f n;
		Vec3f t; 
		std::vector<ProtoFace3*> fs;
		for (int j = 0; j < faces.size(); j++) {
			if (&verts.at(i) == faces.at(j)[0] || &verts.at(i) == faces.at(j)[1] ||
				&verts.at(i) == faces.at(j)[2]) {
				n += faces.at(j).getNorm();
				t += faces.at(j).getTangentBM();
				fs.push_back(&faces.at(j));
			}
		}
		geomSets.push_back(ProtoGeomSet(&verts.at(i), fs));
		n.normalize();
		t.normalize();
		verts.at(i).setNormal(n);
		verts.at(i).setTangent(t);
	}
}

void BrittGeom3::calcPrimitives() {
	if (interleavedPrims.size() > 0) { 
		interleavedPrims.clear(); 
	}
	if (indPrims.size() > 0) { 
		indPrims.clear(); 
	}

	for (int i = 0; i < verts.size(); i++) {
		interleavedPrims.push_back(verts.at(i).pos.x);
		interleavedPrims.push_back(verts.at(i).pos.y);
		interleavedPrims.push_back(verts.at(i).pos.z);

		interleavedPrims.push_back(verts.at(i).getNormal().x);
		interleavedPrims.push_back(verts.at(i).getNormal().y);
		interleavedPrims.push_back(verts.at(i).getNormal().z);

		interleavedPrims.push_back(verts.at(i).getColor().getR());
		interleavedPrims.push_back(verts.at(i).getColor().getG());
		interleavedPrims.push_back(verts.at(i).getColor().getB());
		interleavedPrims.push_back(verts.at(i).getColor().getA());

		interleavedPrims.push_back(verts.at(i).getUV().elem0);
		interleavedPrims.push_back(verts.at(i).getUV().elem1);

		interleavedPrims.push_back(verts.at(i).getTangent().x);
		interleavedPrims.push_back(verts.at(i).getTangent().y);
		interleavedPrims.push_back(verts.at(i).getTangent().z);
	}

	for (int i = 0, j = 0; i < inds.size(); i++) {
		indPrims.push_back(inds.at(i).elem0);
		indPrims.push_back(inds.at(i).elem1);
		indPrims.push_back(inds.at(i).elem2);
	}
}

void BrittGeom3::setMaterialMemLocs() {
	diffuse_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "diffuseMaterial");
	ambient_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "ambientMaterial");
	specular_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "specularMaterial");
	emissive_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "emissiveMaterial");
	shininess_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "shininess");
}