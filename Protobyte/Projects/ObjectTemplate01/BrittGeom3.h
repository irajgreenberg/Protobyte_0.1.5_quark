#ifndef __BrittGeom3__Protobyte__
#define __BrittGeom3__Protobyte__

#if defined(_WIN32) || defined(__linux__)
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#if defined(__APPLE__) || defined(__linux__)
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <memory>
#include <sys/stat.h>
#include <sys/types.h>

#include "ProtoMath.h"
#include "ProtoCore.h"
#include "ProtoUtility.h"

#include "ProtoShader.h"
#include "ProtoTexture.h"

#include "ProtoVector2.h"
#include "ProtoVector3.h"
#include "ProtoVector4.h"
#include "ProtoDimension2.h"
#include "ProtoDimension3.h"
#include "ProtoTuple3.h"
#include "ProtoTuple4.h"
#include "ProtoMatrix3.h"
#include "ProtoMatrix4.h"

#include "ProtoFace3.h"
#include "ProtoGeomSet.h"

#include "ProtoColor4.h"

#if defined (_WIN32) || defined (_WIN64)
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace ijg {

#define BUFFER_OFFSET(i) ((void*)(i))

	class BrittGeom3 {
		friend class ProtoVertex3;

	public:
		friend std::ostream& operator <<(std::ostream& out, const BrittGeom3& geom);
		
		enum RenderMode {
			bPOINTS,
			bWIREFRAME,
			bSURFACE
		};

		BrittGeom3();

		virtual ~BrittGeom3();

		//for getters and setters - should Vec3f attributes be
		//separated into compontents (x, y, z)?

		//GETTERS:
		virtual Vec3f getPos() const;
		virtual Vec3f getRot() const;
		virtual Dim3f getSize() const;
		//should color be returned as vector and single color
		//or just as single color?
		virtual std::vector<ProtoColor4f> getColor() const;
		virtual ProtoColor4f getColorAt(int position) const;
		virtual Vec3f getSpd() const;
		virtual Vec3f getRotSpd() const;

		//SETTERS:
		virtual void setPos(const Vec3f& newPos);
		virtual void setRot(const Vec3f& newRot);
		virtual void setSize(const Dim3f& newSize);
		//vector or single color?
		virtual void setColor(const std::vector<ProtoColor4f>& newColor);
		virtual void setColorAt(int position, const ProtoColor4f& newColor);
		virtual void setSpd(const Vec3f& newSpd);
		virtual void setRotSpd(const Vec3f& newRotSpd);

	protected:
		enum { STRIDE = 15 };
		
		Vec3f pos, rot;
		Dim3f size;
		//removed single color component - vector only
		std::vector<ProtoColor4f> color;
		//necessary? - move and rotate functions in future?
		Vec3f spd, rotSpd;

		std::vector<ProtoVertex3> verts;
		std::vector<ProtoTuple3<int>> inds;

		std::vector<float> interleavedPrims;

		ProtoTexture diffuseMapTexture, bumpMapTexture, reflectionMapTexture, refractionMapTexture, specularMapTexture;

		std::string diffuseMapImage, bumpMapImage, reflectionMapImage, refractionMapImage, specularMapImage;

		GLint diffuseMapLoc, bumpMapLoc;
		std::vector<std::string> diffuseTextureImageURLs;

		Vec2f textureScale;

		GLuint vaoID;
		GLuint vboID, indexVboID;
		float* sharedMemPointer;

		std::vector<ProtoGeomSet> geomSets;

		//virtual void calcVerts() = 0;
		//virtual void calcInds() = 0;

		//private or protected?s
		void clearColor();
		void clearVectors();

		void init();
		void calcFaces();
		void calcVertexNorms();
		void calcPrimitives();

		//void createDiffuseMapTexture(const std::string& diffuseMapImage);
		//void createBumpMapTexture(const std::string& bumpMapImage); 
		//void createReflectionMapTexture(const std::string& reflectioneMapImage); 
		//void createRefractionMapTexture(const std::string& refractionMapImage); 
		//void createSpecularMapTexture(const std::string& specularMapImage); 

	private:


	};

	inline Vec3f BrittGeom3::getPos() const {
		return pos;
	}

	inline Vec3f BrittGeom3::getRot() const {
		return rot;
	}

	inline Dim3f BrittGeom3::getSize() const {
		return size;
	}

	inline std::vector<ProtoColor4f> BrittGeom3::getColor() const {
		return color;
	}

	inline ProtoColor4f BrittGeom3::getColorAt(int position) const {
		int max = color.size() - 1;
		if (position < 0) {
			position = 0;
		}
		else if (position > max) {
			position = max;
		}
		return color.at(position);
	}

	inline Vec3f BrittGeom3::getSpd() const {
		return spd;
	}

	inline Vec3f BrittGeom3::getRotSpd() const {
		return rotSpd;
	}

	inline void BrittGeom3::setPos(const Vec3f& newPos) {
		pos = newPos;
	}

	inline void BrittGeom3::setRot(const Vec3f& newRot) {
		rot = newRot;
	}

	inline void BrittGeom3::setSize(const Dim3f& newSize) {
		size = newSize;
	}

	inline void BrittGeom3::setColor(const std::vector<ProtoColor4f>& newColor) {
		clearColor();
		color = newColor;
	}

	inline void BrittGeom3::setColorAt(int position, const ProtoColor4f& newColor) {
		int max = color.size() - 1;
		if (position < 0) {
			position = 0;
		}
		else if (position > max) {
			color.push_back(newColor);
		}
		else {
			color[position] = newColor;
		}
	}

	inline void BrittGeom3::setSpd(const Vec3f& newSpd) {
		spd = newSpd;
	}

	inline void BrittGeom3::setRotSpd(const Vec3f& newRotSpd) {
		rotSpd = newRotSpd;
	}

}

#endif