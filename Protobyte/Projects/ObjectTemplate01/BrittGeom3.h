#ifndef __BrittGeom3__Protobyte__
#define __BrittGeom3__Protobyte__

#include <iostream>
#include <vector>
#include <memory>

#include "ProtoShader.h"

#include "ProtoGeomSet.h"
#include "ProtoTexture.h"

#include "ProtoVertex3.h"
#include "ProtoFace3.h"s
#include "ProtoTuple3.h"

namespace ijg {
	class BrittGeom3 {
		
	public:
		BrittGeom3();
		~BrittGeom3();

		void display();

	protected:
		struct Material {
			Col4f diffuse;
			Col4f ambient;
			Col4f specular;
			Col4f emissive;
			float shininess;

			//added implementation for default materials constuctor
			Material():
				diffuse(defaultDiffuse), ambient(defaultAmbient), specular(defaultSpecular), emissive(defaultEmissive), shininess(defaultShininess) {
			}

			Material(const Col4f& diffuse, const Col4f& ambient, const Col4f& specular, const Col4f& emissive, float shininess) :
				diffuse(diffuse), ambient(ambient), specular(specular), emissive(emissive), shininess(shininess){}

		private:
			Col4f defaultDiffuse = Col4f(0.7, 0.7, 0.7, 1.0);
			Col4f defaultAmbient = Col4f(0.125, 0.125, 0.125, 1.0);
			Col4f defaultSpecular = Col4f(0.2, 0.2, 0.2, 1.0);
			Col4f defaultEmissive = Col4f(0.0, 0.0, 0.0, 1.0);
			float defaultShininess = 8.0;
		};

		Material materials;

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

		std::vector<ProtoFace3> faces;

		//Primitives
		std::vector<unsigned int> indPrims;
		std::vector<float> interleavedPrims;

		//Open GL and GLEW
		GLuint vaoID;
		GLuint vboID, indexVboID;

		GLint diffuseMapLoc;

		//Material Uniform Locations
		GLuint diffuse_loc_U, ambient_loc_U, specular_loc_U, emissive_loc_U, shininess_loc_U;

		std::vector<ProtoGeomSet> geomSets;

		void calcFaces();
		void calcVertexNorms();
		void calcPrimitives();

		void setMaterialMemLocs();
		void initializeGLEW();
		void initializeOpenGL();

		void createDiffuseMapTexture(const std::string& diffuseMapImage);

	};
}
#endif