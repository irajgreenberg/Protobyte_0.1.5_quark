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

#include "ProtoShape3.h"

#if defined (_WIN32) || defined (_WIN64)
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define SURFACE ProtoShape3::RenderMode::SURFACE
#define WIREFRAME ProtoShape3::RenderMode::WIREFRAME
#define POINTS ProtoShape3::RenderMode::POINTS

namespace ijg {

#define BUFFER_OFFSET(i) ((void*)(i))

	class BrittGeom3 {
		friend class ProtoVertex3;

	protected:
		struct Material {
			Col4f diffuse;
			Col4f ambient;
			Col4f specular;
			Col4f emissive;
			float shininess;

			// cstrs
			//implement default constructor!!
			Material(){}
			Material(const Col4f& diffuse, const Col4f& ambient, const Col4f& specular, const Col4f& emissive, float shininess) :
				diffuse(diffuse), ambient(ambient), specular(specular), emissive(emissive), shininess(shininess){}

		};

	public:
		friend std::ostream& operator <<(std::ostream& out, const BrittGeom3& geom);
		
//		enum RenderMode {
//			bPOINTS,
//			bWIREFRAME,
//			bSURFACE
//		};

		static GLuint textureID;

		//make protected or private
		std::vector<float> packedFaces;
		std::vector<ProtoFace3> faces;
		std::vector<ProtoFace3> faces2;

		BrittGeom3();

		virtual ~BrittGeom3();

		virtual void display(ProtoShape3::RenderMode render = SURFACE, float pointSize = 0.5);

		//necessary? useful?
		virtual void move(const Vec3f& v);
		virtual void rotate(const Vec3f& v);
		virtual void scale(const ProtoDimension3f& s);
		virtual void transform(const ProtoMatrix4f& mat4);

		void sortFaces();
		void enableNormalMap(float depth = 0.5);
		void disableNormalMap();
		void textureOn();
		void textureOff();

		//for getters and setters - should Vec3f attributes be
		//separated into compontents (x, y, z)?

		//GETTERS:
		virtual Vec3f getPos() const;
		virtual Vec3f getRot() const;
		virtual Dim3f getSize() const;
		//should color be returned as vector and single color
		//or just as single color?
		//virtual std::vector<ProtoColor4f> getColor() const;
		//virtual ProtoColor4f getColorAt(int position) const;
		virtual Vec3f getSpd() const;
		virtual Vec3f getRotSpd() const;

		std::vector<ProtoFace3>& getFaces();
		std::vector<ProtoVertex3>& getVertices();
		std::vector<float>& getInterleavedPrims();

		const Col4f& getDiffuseMaterial() const;
		const Col4f& getAmbientMaterial() const;
		const Col4f& getSpecularMaterial() const;
		const Col4f& getEmissiveMaterial() const;
		float getShininess();

		Vec2f getTextureScale() const;

		const Material& getMaterials() const;

		std::vector<Tup4v> getGeomData();

		GLuint getVboID() const;
		GLuint getIndexVboID() const;
		int getIndicesSize() const;

		//SETTERS:
		virtual void setPos(const Vec3f& newPos);
		virtual void setRot(const Vec3f& newRot);
		virtual void setSize(const Dim3f& newSize);
		//vector or single color?
		//virtual void setColor(const std::vector<ProtoColor4f>& newColor);
		//virtual void setColorAt(int position, const ProtoColor4f& newColor);
		virtual void setSpd(const Vec3f& newSpd);
		virtual void setRotSpd(const Vec3f& newRotSpd);

		void setBumpMap(const std::string& bumpMapImage);
		void loadBumpMapTexture(const std::string& bumpMapImage); // loc 1 // pre-made normal map
		void setDiffuseMap(const std::string& diffuseMapImage);
		void setReflectionMap(const std::string& reflectionMapImage);
		void setRefractionMap(const std::string& refractionMapImage);
		void setSpecularMap(const std::string& specularMapImage);

		void setDiffuseMaterial(const Col4f& diffuseMaterial);
		void setAmbientMaterial(const Col4f& ambientMaterial);
		void setSpecularMaterial(const Col4f& specularMaterial);
		void setEmissiveMaterial(const Col4f& emissiveMaterial);
		void setShininess(float shininess);

		void setTextureScale(const Vec2f& textureScale);

		void setMaterials(const Material& materials);

	protected:
		enum { STRIDE = 15 };
		
	public:
		Vec3f pos, rot;
		Dim3f size;
		//change name of colors
		ProtoColor4f col4;
		std::vector<ProtoColor4f> col4s;
		//necessary? - move and rotate functions in future?
		Vec3f spd, rotSpd;

	protected:

		Material materials;

		const ProtoShader* shader;

		bool isTextureEnabled;

		std::vector<ProtoVertex3> verts;
		std::vector<ProtoTuple3<int>> inds;

		std::vector<float> interleavedPrims;
		std::vector<unsigned int> indPrims;

		ProtoTexture diffuseMapTexture, bumpMapTexture, reflectionMapTexture, refractionMapTexture, specularMapTexture;

		std::string diffuseMapImage, bumpMapImage, reflectionMapImage, refractionMapImage, specularMapImage;

		GLuint displayListIndex;

		// material uniform locations 
		GLuint diffuse_loc_U, ambient_loc_U, specular_loc_U, emissive_loc_U, shininess_loc_U;

		GLint diffuseMapLoc, bumpMapLoc;
		std::vector<std::string> diffuseTextureImageURLs;

		Vec2f textureScale;

		GLuint vaoID;
		GLuint vboID, indexVboID;
		float* sharedMemPointer;

		std::vector<ProtoGeomSet> geomSets;

		virtual void calcVerts() = 0;
		virtual void calcInds() = 0;

		//private or protected?s
		void clearColor();
		void clearVectors();

		void init();
		void calcFaces();
		void calcVertexNorms();
		void calcPrimitives();

		void setShader(const ProtoShader* newShader);

		void createDiffuseMapTexture(const std::string& diffuseMapImage);
		void createBumpMapTexture(const std::string& bumpMapImage); 
		void createReflectionMapTexture(const std::string& reflectioneMapImage); 
		void createRefractionMapTexture(const std::string& refractionMapImage); 
		void createSpecularMapTexture(const std::string& specularMapImage); 

		void updateBuffer();
		void updateTextureBuffer();
		void updateColorBuffer();

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

//	inline std::vector<ProtoColor4f> BrittGeom3::getColor() const {
//		return color;
//	}

//	inline ProtoColor4f BrittGeom3::getColorAt(int position) const {
//		int max = color.size() - 1;
//		if (position < 0) {
//			position = 0;
//		}
//		else if (position > max) {
//			position = max;
//		}
//		return color.at(position);
//	}

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

//	inline void BrittGeom3::setColor(const std::vector<ProtoColor4f>& newColor) {
//		clearColor();
//		color = newColor;
//	}

//	inline void BrittGeom3::setColorAt(int position, const ProtoColor4f& newColor) {
//		int max = color.size() - 1;
//		if (position < 0) {
//			position = 0;
//		}
//		else if (position > max) {
//			color.push_back(newColor);
//		}
//		else {
//			color[position] = newColor;
//		}
//	}

	inline void BrittGeom3::setSpd(const Vec3f& newSpd) {
		spd = newSpd;
	}

	inline void BrittGeom3::setRotSpd(const Vec3f& newRotSpd) {
		rotSpd = newRotSpd;
	}

	inline std::vector<ProtoFace3>& BrittGeom3::getFaces() {
		return faces;
	}

	inline std::vector<ProtoVertex3>& BrittGeom3::getVertices() {
		return verts;
	}

	inline  std::vector<float>& BrittGeom3::getInterleavedPrims(){
		return interleavedPrims;
	}

	inline void BrittGeom3::setTextureScale(const Vec2f& textureScale) {
		this->textureScale = textureScale;
		updateTextureBuffer();
	}

	inline Vec2f BrittGeom3::getTextureScale() const {
		return textureScale;
	}

	inline GLuint BrittGeom3::getVboID() const {
		return vboID;
	}

	inline GLuint BrittGeom3::getIndexVboID() const {
		return indexVboID;
	}

	inline int BrittGeom3::getIndicesSize() const{
		return static_cast<int>(inds.size());
	}

	// materials
	inline void BrittGeom3::setDiffuseMaterial(const Col4f& diffuseMaterial){
		materials.diffuse = diffuseMaterial;

		diffuse_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "diffuseMaterial");
		//init();
	}

	inline void BrittGeom3::setAmbientMaterial(const Col4f& ambientMaterial){
		materials.ambient = ambientMaterial;

		ambient_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "ambientMaterial");
		//init();
	}
	inline void BrittGeom3::setSpecularMaterial(const Col4f& specularMaterial){
		materials.specular = specularMaterial;

		specular_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "specularMaterial");
		//init();
	}

	inline void BrittGeom3::setEmissiveMaterial(const Col4f& emissiveMaterial){
		materials.emissive = emissiveMaterial;

		emissive_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "emissiveMaterial");
		//init();
	}

	inline void BrittGeom3::setShininess(float shininess){
		materials.shininess = shininess;
		//init();
	}

	inline const Col4f& BrittGeom3::getDiffuseMaterial() const{
		return materials.diffuse;
	}
	inline const Col4f& BrittGeom3::getAmbientMaterial() const{
		return materials.ambient;
	}
	inline const Col4f& BrittGeom3::getSpecularMaterial() const{
		return materials.specular;
	}
	inline const Col4f& BrittGeom3::getEmissiveMaterial() const{
		return materials.emissive;
	}
	inline float BrittGeom3::getShininess(){
		return materials.shininess;
	}

	inline void BrittGeom3::setMaterials(const Material& materials){
		this->materials = materials;
	}
	inline const BrittGeom3::Material& BrittGeom3::getMaterials() const{
		return materials;
	}
}

#endif