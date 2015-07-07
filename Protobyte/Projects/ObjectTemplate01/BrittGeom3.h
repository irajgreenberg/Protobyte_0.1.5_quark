#ifndef __BrittGeom3__Protobyte__
#define __BrittGeom3__Protobyte__

#if defined(_WIN32) || defined(__linux__)
#define GLEW_STATIC // link to glew32s instead of including dll
#include <GL/glew.h>
#endif

#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>

// preproc dir for relative resource loading
// from http://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
// http://www.daniweb.com/software-development/cpp/threads/202937/ifdef-with-boolean-and-or
#include <stdio.h>  /* defines FILENAME_MAX */
#if defined (_WIN32) || defined (_WIN64)
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
// end relative loading proproc dir

#include "ProtoShader.h"

#include "ProtoGeomSet.h"
#include "ProtoTexture.h"

#include "ProtoVertex3.h"
#include "ProtoFace3.h"
#include "ProtoTuple3.h"

namespace ijg {

#define BUFFER_OFFSET(i) ((void*)(i))

	class BrittGeom3 {
		
	public:
		static GLuint textureID;
		std::vector<std::string> diffuseTextureImageURLs;

		BrittGeom3();
		~BrittGeom3();

		void display();

	protected:
		std::vector<ProtoVertex3> verts;
		std::vector<ProtoTuple3<int>> inds;
		Vec2f textureScale;

		std::string diffuseMapImage;

		//make private and create getter and setter
		std::vector<Col4f> color;

		void init();

		void clearVectors();

		virtual void calcVerts() = 0;
		virtual void calcInds() = 0;

	private:
		enum {
			STRIDE = 15
		};

		struct Material {
			Col4f diffuse;
			Col4f ambient;
			Col4f specular;
			Col4f emissive;
			float shininess;

			//added implementation for default materials constuctor
			Material() :
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

		bool isTextureEnabled;

		std::vector<ProtoFace3> faces;

		
		ProtoTexture diffuseMapTexture;
		GLint diffuseMapLoc;

		std::vector<ProtoGeomSet> geomSets;

		//Primitives
		std::vector<unsigned int> indPrims;
		std::vector<float> interleavedPrims;

		//Material Uniform Locations
		GLuint diffuse_loc_U, ambient_loc_U, specular_loc_U, emissive_loc_U, shininess_loc_U;

		//Open GL and GLEW
		GLuint vaoID;
		GLuint vboID, indexVboID;

		void calcFaces();
		void calcVertexNorms();
		void calcPrimitives();

		void setMaterialMemLocs();
		void initializeGLEW();
		void initializeBuffers();

		void createDiffuseMapTexture(const std::string& diffuseMapImage);
	};
}
#endif