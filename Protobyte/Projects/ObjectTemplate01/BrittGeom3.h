#ifndef __BrittGeom3__Protobyte__
#define __BrittGeom3__Protobyte__

#include <iostream>
#include <vector>
#include <memory>

#include "ProtoShader.h"

#include "ProtoGeomSet.h"
#include "ProtoTexture.h"

#include "ProtoVertex3.h"
#include "ProtoTuple3.h"

namespace ijg {
	class BrittGeom3 {
		
	public:
		BrittGeom3();
		~BrittGeom3();

		void display();

	protected:
		std::vector<ProtoVertex3> verts;
		std::vector<ProtoTuple3<int>> inds;

		std::vector<Col4f> color;

		Vec2f textureScale;

		std::string diffuseMapImage;
		ProtoTexture diffuseMapTexture;
		

		void init();

		void clearVectors();

		virtual void calcVerts() = 0;
		virtual void calcInds() = 0;

	private:
		enum {
			STRIDE = 15
		};

		//Primitives
		std::vector<unsigned int> indPrims;
		std::vector<float> interleavedPrims;

		//Open GL and GLEW
		GLuint vaoID;
		GLuint vboID, indexVboID;

		GLint diffuseMapLoc;

		std::vector<ProtoGeomSet> geomSets;

		void calcFaces();
		void calcVertexNorms();
		void calcPrimitives();

		void initializeGLEW();
		void initializeOpenGL();

		void createDiffuseMapTexture(const std::string& diffuseMapImage);

	};
}
#endif