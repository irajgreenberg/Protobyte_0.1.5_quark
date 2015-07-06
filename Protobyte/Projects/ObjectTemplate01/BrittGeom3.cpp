#include "BrittGeom3.h"

#define STRIDE ijg::BrittGeom3::STRIDE;

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

	initializeGLEW();
	initializeBuffers();
	isTextureEnabled = true;
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

void BrittGeom3::initializeGLEW() {
#if defined(_WIN32) || defined(__linux__)
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
#endif
}

void BrittGeom3::initializeBuffers() {
	// Special thanks to:
	// http://stackoverflow.com/questions/8704801/glvertexattribpointer-clarification
	// http://www.swiftless.com/tutorials/opengl4/4-opengl-4-vao.html
	/***************************************/
	/*       Setup VAO/VBO buffers         */
	/***************************************/
	// 1. Create and bind VAO
	glGenVertexArrays(1, &vaoID); // Create VAO
	glBindVertexArray(vaoID); // Bind VAO (making it active)
	//2. Create and bind VBO
	// a. Vertex attributes
	glGenBuffers(1, &vboID); // Create VBO ID
	glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind vertex attributes VBO
	int vertsDataSize = sizeof (float)* static_cast<int>(interleavedPrims.size());
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW); // allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data

	// b. Indices  uses ELEMENT_ARRAY_BUFFER
	glGenBuffers(1, &indexVboID); // Generate buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboID); // Bind indices VBO
	int indsDataSize = static_cast<int>(inds.size()) * 3 * sizeof (GL_UNSIGNED_INT);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indsDataSize, NULL, GL_STATIC_DRAW); // allocate
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indsDataSize, &indPrims[0]); // upload the data

	for (int i = 0; i < 5; i++) {
		glEnableVertexAttribArray(i);
	}
	// STRIDE is 15: pos(3) + norm(3) + col(4) + uv(2) + tang(3)
	// (x, y, z, nx, ny, nz, r, g, b, a, u, v, tx, ty, tz)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof (GLfloat), BUFFER_OFFSET(0)); // pos
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof (GLfloat), BUFFER_OFFSET(12)); // norm
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, STRIDE * sizeof (GLfloat), BUFFER_OFFSET(24)); // col
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, STRIDE * sizeof (GLfloat), BUFFER_OFFSET(40)); // uv
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof (GLfloat), BUFFER_OFFSET(48)); // tangent

	// Disable VAO
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}