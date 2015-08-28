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

// include GLM
#include "glm/gtc/type_ptr.hpp" // matrix copying
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"




namespace ijg {

	class ProtoContext {

	private:
		ProtoContext() {} // private cstr for singleton pattern
		static std::shared_ptr<ProtoContext> ctx;

		

		

		// flags for shader locations
		//GLuint M_U, N_U;
		//GLuint T_U, R_U, S_U;
		std::stack <glm::mat4> matrixStack;

		ProtoShader shader;

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
		float viewAngle, aspect, nearDist, farDist;

		// look at
		Vec3 axis, eyePos, axis; 
		
		// orthogonal view 
		float left, right, bottom, top;


		enum ProjectionType {
			PERSPECTIVE,
			ORTHOGONAL
		};
		void setProjection(ProjectionType projType = PERSPECTIVE);
		

	public:
		static const std::shared_ptr<ProtoContext> getContext();
		void init();

		/*** Matrices (4x4) ***/
		glm::mat4 M; // Model
		glm::mat4 V; // View
		glm::mat4 MV; // ModelView
		glm::mat4 P; // Projection
		glm::mat4 MVP; // ModelViewProjection

		// For Shadow map
		glm::mat4 L_V; // Light View
		glm::mat4 L_MV; // Light ModelView
		glm::mat4 L_P; // Light Projection
		glm::mat4 L_B; // Light Bias
		glm::mat4 L_BP; // Light BiasProjection (depth bias)
		glm::mat4 L_MVBP; // Light ModelViewBiasProjection

		/*** Matrices (3x3) ***/
		// Normal
		glm::mat3 N;

		// flags for shader locations
		GLuint M_U, V_U, MV_U, P_U, MVP_U, N_U;
		//GLuint T_U, R_U, S_U;
		GLuint L_MVBP_U; // only for Light perspective
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
