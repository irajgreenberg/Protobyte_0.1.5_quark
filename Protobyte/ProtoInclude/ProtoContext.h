/*!  \brief  ProtoContext.h: encapsulates static tranformation matrix/functions
ProtoContext.h
Protobyte Library

Copyright (c) 2015 Ira Greenberg. All rights reserved.

Library Usage:
This work is licensed under the Creative Commons
Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit
http://creativecommons.org/licenses/by-nc-sa/3.0/
or send a letter to Creative Commons,
444 Castro Street, Suite 900,
Mountain View, California, 94041, USA.

This notice must be retained in any source distribution.

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#ifndef __PROTO_CONTEXT_H__
#define __PROTO_CONTEXT_H__

// OpenGL drivers
#if defined (_WIN32) || defined(_WIN64)
#define GLEW_STATIC // link to glew32s instead of including dll
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h> // brings in OpenGL

#include <iostream>
#include <stack>
#include <memory>

#include "ProtoVector3.h"
#include "ProtoVector4.h"
#include "ProtoShader.h"
#include "ProtoLight.h"
#include "ProtoColor3.h"

// include GLM
#include "glm/gtc/type_ptr.hpp" // matrix copying
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"




namespace ijg {

	class ProtoContext {

	private:

		static float width;
		static float height;
		ProtoContext() {} // private cstr for singleton pattern
		static std::shared_ptr<ProtoContext> ctx;

		std::stack <glm::mat4> matrixStack;

		//Lighting
		GLint glLights[8];
		enum Light {
			LIGHT_0,
			LIGHT_1,
			LIGHT_2,
			LIGHT_3,
			LIGHT_4,
			LIGHT_5,
			LIGHT_6,
			LIGHT_7
		};
		std::vector<ProtoLight> lights;

		// perspective view 
		float viewAngle{ 75.0f };
		float aspect{ 0.0f };
		float nearDist{ .1f };
		float farDist{ 1500.0f };

		// look at
		Vec3 eyePos, sceneCenter, axis; 
		
		// orthogonal view 
		float left, right, bottom, top;


		enum ProjectionType {
			PERSPECTIVE,
			ORTHOGONAL
		};
		void setProjection(ProjectionType projType = PERSPECTIVE);
		

	public:
		static const std::shared_ptr<ProtoContext> getContext(float width = 100.0f, float height = 100.0f);
		void init();

		/*** Matrices (4x4) ***/
		glm::mat4 modelMatrix; // Model
		glm::mat4 viewMatrix; // View
		glm::mat4 modelViewMatrix; // ModelView
		glm::mat4 projectionMatrix; // Projection
		glm::mat4 modelViewProjectionMatrix; // ModelViewProjection

		// For Shadow map
		glm::mat4 lightViewMatrix; // Light View
		glm::mat4 lightModelViewMatrix; // Light ModelView
		glm::mat4 lightProjectionMatrix; // Light Projection
		glm::mat4 lightDepthBiasMatrix; // Light Bias
		glm::mat4 lightDepthBiasProjectionMatrix; // Light BiasProjection (depth bias)
		glm::mat4 lightModelViewDepthBiasProjectionMatrix;// Light ModelViewBiasProjection
		glm::mat4 shadowMatrix;
		/*** Matrices (3x3) ***/
		// Normal
		glm::mat3 normalMatrix;

		// flags for shader locations
		GLuint globalAmbient_U;
		GLuint model_U, view_U, modelView_U, projection_U, modelViewProjection_U, normal_U;
		GLuint L_MVBP_U, lightModelViewDepthBiasProjection_U; // only for Light perspective
		GLuint shaderPassFlag_U;
		const GLuint& getShaderPassFlag_U();
		void setShaderPassFlag_U(const GLuint& shaderPassFlag_U);

		// Uniform Shadow Map
		GLuint shadowMap_U;
		const GLuint& getShadowMap_U();
		void setShadowMap_U(const GLuint& shadowMap_U);

		// Uniform Lighting factors
		// enable/disable lighting factors for 2D rendering
		Vec4f lightRenderingFactors;
		GLuint lightRenderingFactors_U;
		const Vec4f& getLightRenderingFactors();
		void setLightRenderingFactors(const Vec4f& lightRenderingFactors);
		const GLuint& getLightRenderingFactors_U();
		void setLightRenderingFactors_U(const GLuint& lightRenderingFactors_U);
		

		// shadow mapping texture id's
		GLuint shadowBufferID, shadowTextureID;

		// flag for shadowing
		bool areShadowsEnabled;

		const int SHADOWMAP_WIDTH = 4096, SHADOWMAP_HEIGHT = 4096;
		
		
		bool areShadowsOn;
		void setShadowsOn(bool areShadowsOn);
		void shadowsOn();
		void shadowOff();

		Col3f globalAmbient; // make private

		// Geometry Matrix set/get Functions
		void setModelMatrix(const glm::mat4& modelMatrix);
		void setViewMatrix(const glm::mat4& viewMatrix);
		void setProjectionMatrix(const glm::mat4& projectionMatrix);
		void concatenateModelViewMatrix();
		void concatenateModelViewProjectionMatrix();
		void createNormalMatrix();
		// get
		const glm::mat4& getModelMatrix();
		const glm::mat4& getViewMatrix();
		const glm::mat4& getModelViewMatrix();
		const glm::mat4& getProjectionMatrix();
		const glm::mat4& getModelViewProjectionMatrix();
		const glm::mat3& getNormalMatrix();


		// Light Matrix Functions (for shadow map)
		void setLightViewMatrix(const glm::mat4& lightViewMatrix);
		void setLightDepthBiasMatrix(const glm::mat4& lightDepthBiasMatrix);
		void setLightProjectionMatrix(const glm::mat4& lightProjectionMatrix);
		void concatenateLightModelViewMatrix();
		void concatenateDepthBiasProjectionMatrix();
		void concatenateLightModelViewDepthBiasProjectionMatrix();
		
		void concatenateShadowMatrix();
		const glm::mat4& getShadowMatrix();

		const glm::mat4& getLightViewMatrix(); 
		const glm::mat4& getLightModelViewMatrix();
		const glm::mat4& getLightProjectionMatrix(); 
		const glm::mat4& getLightDepthBiasMatrix(); 
		const glm::mat4& getLightModelViewDepthBiasProjectionMatrix();

		

		// lighting
		void setGlobalAmbient(const Col3f& globalAmbient);
		const Col3f& getGlobalAmbient();
		const GLuint& getGlobalAmbient_U();
		void setLight(int index, const Vec3& pos, const Vec3& intensity);
		const ProtoLight& getLight(int index);

		// Uniform Lighting location vars
		struct Light_U {
			GLuint position;
			GLuint intensity;
			GLuint diffuse;
			GLuint ambient;
			GLuint specular;;
		};

		Light_U lights_U[8];


		const Light_U& getLight_U(int index);
		const GLuint getLightModelViewDepthBiasProjection_U();


		// look at
		void setSceneCenter(const Vec3& axis);
		void setEyePosition(const Vec3& eyePos);
		void setUpAxis(const Vec3& axis);

		// perspective view
		void setViewAngle(float viewAngle);
		void setAspect(float aspect);
		void setNearDist(float nearDist);
		void setFarDist(float farDist);

		// orthoonal view
		void setLeft(float left);
		void setRight(float right);
		void setBottom(float bottom);
		void setTop(float top);
	

		void translate(float tx, float ty, float tz);
		void translate(const Vec3f& tXYZ);
		void rotate(float angle, float axisX, float axisY, float axisZ);
		void rotate(float angle, const Vec3f& rXYZ);
		void scale(float s);
		void scale(float sx, float sy, float sz);
		void scale(const Vec3f& sXYZ);
		//implements transform matrix stack
		void concat();
		void push();
		void pop();
	};

	// Geometry matrix set/get functions
	inline void ProtoContext::setModelMatrix(const glm::mat4& modelMatrix) {
		this->modelMatrix = modelMatrix;
	}

	inline void ProtoContext::setViewMatrix(const glm::mat4& viewMatrix) {
		this->viewMatrix = viewMatrix;
	}

	inline void ProtoContext::setProjectionMatrix(const glm::mat4& projectionMatrix) {
		this->projectionMatrix = projectionMatrix;
	}

	// Matrix concatenations functions
	// MV Mat4
	inline void ProtoContext::concatenateModelViewMatrix() {
		modelViewMatrix = viewMatrix * modelMatrix;
	}
	// MVP Mat4
	inline void ProtoContext::concatenateModelViewProjectionMatrix() {
		modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;
	}

	// shadow map
	inline void ProtoContext::setLightViewMatrix(const glm::mat4& lightViewMatrix) {
		this->lightViewMatrix = lightViewMatrix;
	}

	inline void ProtoContext::setLightDepthBiasMatrix(const glm::mat4& lightDepthBiasMatrix) {
		this->lightDepthBiasMatrix; // Light Bias = depthBiasMatrix;
	}

	inline void ProtoContext::setLightProjectionMatrix(const glm::mat4& lightProjectionMatrix) {
		this->lightProjectionMatrix = lightProjectionMatrix;
	}

	// shadow map concatenations functions
	// MV Mat4
	inline void ProtoContext::concatenateLightModelViewMatrix() {
		lightModelViewMatrix = glm::lookAt(glm::vec3(lights.at(0).getPosition().x, lights.at(0).getPosition().y, lights.at(0).getPosition().z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}

	inline void ProtoContext::concatenateDepthBiasProjectionMatrix() {
		lightDepthBiasProjectionMatrix = lightDepthBiasMatrix * lightProjectionMatrix;
	}

	inline void ProtoContext::concatenateLightModelViewDepthBiasProjectionMatrix() {
		//L_MVBP = L_BP*L_MV
		lightModelViewDepthBiasProjectionMatrix = lightDepthBiasProjectionMatrix*lightModelViewMatrix;
	}

	inline void ProtoContext::concatenateShadowMatrix() {
		lightModelViewDepthBiasProjectionMatrix*modelMatrix;
	}

	// geometry matrices
	inline const glm::mat4& ProtoContext::getModelMatrix() {
		return modelMatrix;
	}

	inline const glm::mat4& ProtoContext::getViewMatrix() {
		return viewMatrix;
	}

	inline const glm::mat4& ProtoContext::getModelViewMatrix() {
		return modelViewMatrix;
	}

	inline const glm::mat4& ProtoContext::getProjectionMatrix() {
		return projectionMatrix;
	}

	inline const glm::mat4& ProtoContext::getModelViewProjectionMatrix() {
		return modelViewProjectionMatrix;
	}

	inline const glm::mat3& ProtoContext::getNormalMatrix() {
		return normalMatrix;
	}
	
	// light matrices (for shadow map)
	inline const glm::mat4& ProtoContext::getLightViewMatrix() {
		return lightViewMatrix;
	}

	inline const glm::mat4& ProtoContext::getLightModelViewMatrix() {
		return lightModelViewMatrix;
	}
	
	inline const glm::mat4& ProtoContext::getLightProjectionMatrix() {
		return lightProjectionMatrix;
	}
	
	inline const glm::mat4& ProtoContext::getLightDepthBiasMatrix() {
		return lightDepthBiasMatrix;
	}
	
	inline const glm::mat4& ProtoContext::getLightModelViewDepthBiasProjectionMatrix() {
		return lightModelViewDepthBiasProjectionMatrix;
	}

	inline const glm::mat4& ProtoContext::getShadowMatrix() {
		return shadowMatrix;
	}
	
	
	// Lighting
	inline const Col3f&  ProtoContext::getGlobalAmbient() {
		return globalAmbient;
	}

	inline const GLuint& ProtoContext::getGlobalAmbient_U() {
		return globalAmbient_U;
	}

	inline const ProtoContext::Light_U& ProtoContext::getLight_U(int index) {
		return lights_U[index];
	}


	// N Mat3
	inline void ProtoContext::createNormalMatrix() {
		normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelViewMatrix)));
	}

	// lighting
	inline void ProtoContext::setGlobalAmbient(const Col3f& globalAmbient) {
		this->globalAmbient = globalAmbient;
		glUniform3fv(globalAmbient_U, 1, &globalAmbient.r);
	}

	inline void ProtoContext::setLight(int index, const Vec3& pos, const Vec3& intensity) {
		lights[index].setPosition(pos);
		lights[index].setIntensity(intensity);
		glUniform3fv(lights_U[index].position, 1, &lights[index].getPosition().x);
		glUniform3fv(lights_U[index].intensity, 1, &lights[index].getIntensity().x);
	}

	inline const ProtoLight& ProtoContext::getLight(int index) {
		return lights.at(index);
	}

	inline const GLuint ProtoContext::getLightModelViewDepthBiasProjection_U() {
		return lightModelViewDepthBiasProjection_U;
	}

	inline const Vec4f& ProtoContext::getLightRenderingFactors() {
		return lightRenderingFactors;
	}
	
	inline void ProtoContext::setLightRenderingFactors(const Vec4f& lightRenderingFactors) {
		this->lightRenderingFactors = lightRenderingFactors;
	}
	
	inline const GLuint& ProtoContext::getLightRenderingFactors_U() {
		return lightRenderingFactors_U;
	}

	inline void ProtoContext::setLightRenderingFactors_U(const GLuint& lightRenderingFactors_U) {
		this->lightRenderingFactors_U = lightRenderingFactors_U;
	}

	inline const GLuint& ProtoContext::getShadowMap_U() {
		return shadowMap_U;
	}

	inline void ProtoContext::setShadowMap_U(const GLuint& shadowMap_U) {
		this->shadowMap_U = shadowMap_U;
	}

	inline const GLuint& ProtoContext::getShaderPassFlag_U() {
		return shaderPassFlag_U;
	}

	inline void ProtoContext::setShaderPassFlag_U(const GLuint& shaderPassFlag_U) {
		this->shaderPassFlag_U = shaderPassFlag_U;
	}

	inline void ProtoContext::setSceneCenter(const Vec3& axis) {

	}
	inline void ProtoContext::setEyePosition(const Vec3& eyePos) {

	}
	inline void ProtoContext::setUpAxis(const Vec3& axis) {

	}
}

#endif // __PROTO_CONTEXT_H__
