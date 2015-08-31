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

		//ProtoShader shader;

		// maybes
		//void _initUniforms(ProtoShader* shader_ptr);
		
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

		/*** Matrices (3x3) ***/
		// Normal
		glm::mat3 normalMatrix;

		// flags for shader locations
		// flags for shader locations
		GLuint model_U, view_U, modelView_U, projection_U, modelViewProjection_U, normal_U;
		GLuint L_MVBP_U, lightModelViewDepthBiasProjection_U; // only for Light perspective
		GLuint shaderPassFlag_U;

		// Uniform Shadow Map
		GLuint shadowMap_U;

		// Uniform Lighting factors
		// enable/disable lighting factors for 2D rendering
		Vec4f ltRenderingFactors;
		GLuint lightRenderingFactors_U;
		

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

		

		// lighting
		void setGlobalAmbient(const Col3f& globalAmbient);
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

		GLuint globalAmbient_U;


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
}

#endif // __PROTO_CONTEXT_H__
