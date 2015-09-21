/*!  \brief  ProtoContext.cpp: encapsulates static tranformation matrix/functions
ProtoContext.cpp
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

#include "ProtoContext.h"
using namespace ijg;

float ProtoContext::width{ 0.0f };
float ProtoContext::height{ 0.0f };

// initialize static vars
std::shared_ptr<ProtoContext> ProtoContext::ctx = nullptr;


const std::shared_ptr<ProtoContext> ProtoContext::getContext(float width, float height) {
	ProtoContext::width = width;
	ProtoContext::height = height;
	if (!ProtoContext::ctx){
		ProtoContext::ctx = std::shared_ptr<ProtoContext>(new ProtoContext());
	}
	return ProtoContext::ctx;
}


// shoudl only be callsed by ProtoBaseApp
void ProtoContext::init(){
	static int counter = 0;
	if (counter++ == 0) {// just 1 time
		lights.push_back(ProtoLight());
		lights.push_back(ProtoLight());
		lights.push_back(ProtoLight());
		lights.push_back(ProtoLight());
		lights.push_back(ProtoLight());
		lights.push_back(ProtoLight());
		lights.push_back(ProtoLight());
		lights.push_back(ProtoLight());
	
	//	ctx->setViewMatrix(glm::lookAt(glm::vec3(0.0, 0.0, 1560), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)));
	//	ctx->concatenateModelViewMatrix();
	//	ctx->createNormalMatrix();

		for (int i = 0; i < 1; ++i){
			std::string pos = "lights[" + std::to_string(i) + "].position"; 
			//trace("pos =", pos);
			lights_U[i].position = glGetUniformLocation(ProtoShader::getID_2(), pos.c_str());

			std::string inten = "lights[" + std::to_string(i) + "].intensity";
			lights_U[i].intensity = glGetUniformLocation(ProtoShader::getID_2(), inten.c_str());

			// eventually get rid of these probably
			std::string diff = "lights[" + std::to_string(i) + "].diffuse";
			lights_U[i].diffuse = glGetUniformLocation(ProtoShader::getID_2(), diff.c_str());

			std::string amb = "lights[" + std::to_string(i) + "].ambient";
			lights_U[i].ambient = glGetUniformLocation(ProtoShader::getID_2(), amb.c_str());

			std::string spec = "lights[" + std::to_string(i) + "].specular";
			lights_U[i].specular = glGetUniformLocation(ProtoShader::getID_2(), spec.c_str());
		}

		// global ambient light
		globalAmbient_U = glGetUniformLocation(ProtoShader::getID_2(), "globalAmbientLight");
		//aspect = width / height;
	//	ctx->setProjectionMatrix(glm::perspective(viewAngle, aspect, nearDist, farDist));
	//	ctx->concatenateModelViewProjectionMatrix();
		//MVP = P * MV;

		// START Shadow Map Matrices
		
		//L_MV = glm::lookAt(glm::vec3(lights.at(0).getPosition().x, lights.at(0).getPosition().y, lights.at(0).getPosition().z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		//ctx->setLightViewMatrix(glm::lookAt(glm::vec3(lights.at(0).getPosition().x, lights.at(0).getPosition().y, lights.at(0).getPosition().z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
		//L_P = glm::perspective(45.0f, 1.0f, .10f, 1000.0f);

		//L_P = glm::frustum(-.1f, .1f, -.1f, .1f, .1f, 2000.0f);
		//ctx->setLightProjectionMatrix(glm::frustum(-.1f, .1f, -.1f, .1f, .1f, 2000.0f));
		//setLightProjectionMatrix(glm::ortho<float>(-10, 10, -10, 10, -10, 20));


		//L_P = glm::perspective(50.0f, 1.0f, .10f, 325.0f);
		//L_B = glm::scale(glm::translate(glm::mat4(1), glm::vec3(.5, .5, .5)), glm::vec3(.5, .5, .5));
		//L_B = glm::mat4(1.0);

	//	float ratio{ width / height };
		//L_B = glm::mat4(
		//	glm::vec4(.35, 0.0f, 0.0f, 0.0f),
		//	glm::vec4(0.0f, .35, 0.0f, 0.0f),
		//	glm::vec4(0.0f, 0.0f, 1, 0.0f),
		//	glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
		//);

		//L_B = glm::mat4(
		//	glm::vec4(.5, 0.0f, 0.0f, 0.0f),
		//	glm::vec4(0.0f, .5, 0.0f, 0.0f),
		//	glm::vec4(0.0f, 0.0f, .5, 0.0f),
		//	glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
		//	);
		//ctx->setLightDepthBiasMatrix(glm::mat4(
		//	glm::vec4(.5, 0.0f, 0.0f, 0.0f),
		//	glm::vec4(0.0f, .5, 0.0f, 0.0f),
		//	glm::vec4(0.0f, 0.0f, .5, 0.0f),
		//	glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
		//	));


		//L_BP = L_B*L_P;
	//	ctx->concatenateDepthBiasProjectionMatrix();
	//	ctx->concatenateLightModelViewDepthBiasProjectionMatrix();
		//L_MVBP = L_BP*L_MV;
		// END Shadow Matrices

		//createShadowMap();

		// Get unifrom locations
		model_U = glGetUniformLocation(ProtoShader::getID_2(), "modelMatrix");
		modelView_U = glGetUniformLocation(ProtoShader::getID_2(), "modelViewMatrix");
		modelViewProjection_U = glGetUniformLocation(ProtoShader::getID_2(), "modelViewProjectionMatrix");
		normal_U = glGetUniformLocation(ProtoShader::getID_2(), "normalMatrix");

		// shadow map and light transformation matrix for shadowmapping
		shadowMap_U = glGetUniformLocation(ProtoShader::getID_2(), "shadowMap");
		lightModelViewBiasProjection_U = glGetUniformLocation(ProtoShader::getID_2(), "shadowModelViewBiasProjectionMatrix");
		// L_MVBP_U

		// pass shadow map texture to shader
		shaderPassFlag_U = glGetUniformLocation(ProtoShader::getID_2(), "shadowPassFlag");
		glUniform1i(shaderPassFlag_U, 1); // controls render pass in shader
		glUniform1i(shadowMap_U, 5);

		// enable/disable lighting factors for 2D rendering
		// default is all on
		lightRenderingFactors_U = glGetUniformLocation(ProtoShader::getID_2(), "lightRenderingFactors");
		//glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);


		//shader_ptr->unbind();
	}
}







// matrix transformation functions, in style of GL 1.0
void ProtoContext::translate(float tx, float ty, float tz){
	model = glm::translate(model, glm::vec3(tx, ty, tz));
	concat();
}
void ProtoContext::translate(const Vec3f& tXYZ){
	model = glm::translate(model, glm::vec3(tXYZ.x, tXYZ.y, tXYZ.z));
	concat();
}
void ProtoContext::rotate(float angle, float axisX, float axisY, float axisZ){
	model = glm::rotate(model, angle, glm::vec3(axisX, axisY, axisZ));
	concat();
}
void ProtoContext::rotate(float angle, const Vec3f& rXYZ){
	model = glm::rotate(model, angle, glm::vec3(rXYZ.x, rXYZ.y, rXYZ.z));
	concat();
}
void ProtoContext::scale(float s){
	model = glm::scale(model, glm::vec3(s, s, s));
	concat();
}
void ProtoContext::scale(float sx, float sy, float sz){
	model = glm::scale(model, glm::vec3(sx, sy, sz));
	concat();
}
void ProtoContext::scale(const Vec3f& sXYZ){
	model = glm::scale(model, glm::vec3(sXYZ.x, sXYZ.y, sXYZ.z));
	concat();
}

void ProtoContext::concat(){
	//M = glm::mat4(1.0f);
	//push();
	//modelViewMatrix =  viewMatrix*modelMatrix;
	concatModelView();
	//createNormal();
	//modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;
	concatModelViewProjection();
	// update in shader
	glUniformMatrix4fv(model_U, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(modelView_U, 1, GL_FALSE, &modelView[0][0]);
	glUniformMatrix4fv(modelViewProjection_U, 1, GL_FALSE, &modelViewProjection[0][0]);
	glUniformMatrix3fv(normal_U, 1, GL_FALSE, &getNormal()[0][0]);

	glm::vec3 ltPos = glm::vec3(lights.at(0).getPosition().x, lights.at(0).getPosition().y, lights.at(0).getPosition().z);
	//L_MV = glm::lookAt(ltPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	lightModelView = glm::lookAt(ltPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	lightBiasProjection = lightBias * lightProjection;
	glm::mat4 temp = lightBiasProjection * lightModelView;
	lightModelViewBiasProjection = temp * model;
	glUniformMatrix4fv(lightModelViewBiasProjection_U, 1, GL_FALSE, &lightModelViewBiasProjection[0][0]);
	
	//pop();
}

void ProtoContext::push(){
	// push current transformation matrix onto stack
	//matrixStack.push(M);
	matrixStack.push(model);

}

// reset transformation matrix with stored matrix on stack
void ProtoContext::pop(){

	// reset current transformation matrix with one on top of stack
	//M = matrixStack.top();
	model = matrixStack.top();

	// pop transformation matrix off top of stack
	matrixStack.pop();

	// rebuild matrices and update on GPU
	concat();
}


