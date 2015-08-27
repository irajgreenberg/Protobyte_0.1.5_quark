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

// initialize static vars
std::shared_ptr<ProtoContext> ProtoContext::ctx = nullptr;
glm::mat4 ProtoContext::M = glm::mat4(1.0f);

GLuint ProtoContext::M_U = 0;
GLuint ProtoContext::V_U = 0;
GLuint ProtoContext::MV_U = 0;
GLuint ProtoContext::P_U = 0;
GLuint ProtoContext::MVP_U = 0;
GLuint ProtoContext::N_U = 0;
//glm::mat4 ProtoContext::T = glm::mat4(1.0f);
//glm::mat4 ProtoContext::R = glm::mat4(1.0f);
//glm::mat4 ProtoContext::S = glm::mat4(1.0f);


const std::shared_ptr<ProtoContext> ProtoContext::getContext() {
	
	// transformation matrices
	//M_U = glGetUniformLocation(ProtoShader::getID_2(), "modelMatrix");
	//MV_U = glGetUniformLocation(ProtoShader::getID_2(), "modelViewMatrix");
	//MVP_U = glGetUniformLocation(ProtoShader::getID_2(), "modelViewProjectionMatrix");
	//N_U = glGetUniformLocation(ProtoShader::getID_2(), "normalMatrix");

	// shadow map and light transformation matrix for shadowmapping
	//shadowMap_U = glGetUniformLocation(shader_ptr->getID(), "shadowMap");
	//L_MVBP_U = glGetUniformLocation(shader_ptr->getID(), "shadowModelViewBiasProjectionMatrix");

	//// pass shadow map texture to shader
	//shaderPassFlag_U = glGetUniformLocation(shader_ptr->getID(), "shadowPassFlag");
	//glUniform1i(shaderPassFlag_U, 1); // controls render pass in shader
	//glUniform1i(shadowMap_U, 5);



	if (!ProtoContext::ctx){
		ProtoContext::ctx = std::shared_ptr<ProtoContext>(new ProtoContext());
		return ProtoContext::ctx;
	} 
	return ProtoContext::ctx;
}

// matrix transformation functions, in style of GL 1.0
void ProtoContext::translate(float tx, float ty, float tz){
	//M = glm::translate(M, glm::vec3(tx, ty, tz));
	M = glm::translate(M, glm::vec3(tx, ty, tz));
	concat();
}
void ProtoContext::translate(const Vec3f& tXYZ){
	//M = glm::translate(M, glm::vec3(tXYZ.x, tXYZ.y, tXYZ.z));
	M = glm::translate(M, glm::vec3(tXYZ.x, tXYZ.y, tXYZ.z));
	concat();
}
void ProtoContext::rotate(float angle, float axisX, float axisY, float axisZ){
	//M = glm::rotate(M, angle, glm::vec3(axisX, axisY, axisZ));
	M = glm::rotate(M, angle, glm::vec3(axisX, axisY, axisZ));
	concat();
}
void ProtoContext::rotate(float angle, const Vec3f& rXYZ){
	//M = glm::rotate(M, angle, glm::vec3(rXYZ.x, rXYZ.y, rXYZ.z));
	M = glm::rotate(M, angle, glm::vec3(rXYZ.x, rXYZ.y, rXYZ.z));
	concat();
}
void ProtoContext::scale(float s){
	//M = glm::scale(M, glm::vec3(s, s, s));
	M = glm::scale(M, glm::vec3(s, s, s));
	concat();
}
void ProtoContext::scale(float sx, float sy, float sz){
	//M = glm::scale(M, glm::vec3(sx, sy, sz));
	M = glm::scale(M, glm::vec3(sx, sy, sz));
	concat();
}
void ProtoContext::scale(const Vec3f& sXYZ){
	//M = glm::scale(M, glm::vec3(sXYZ.x, sXYZ.y, sXYZ.z));
	M = glm::scale(M, glm::vec3(sXYZ.x, sXYZ.y, sXYZ.z));
	concat();
}

void ProtoContext::concat(){
	//M = glm::mat4(1.0f);
	//push();
	MV = V * M;
	N = glm::transpose(glm::inverse(glm::mat3(MV)));
	MVP = P * MV;
	// update in shader
	glUniformMatrix4fv(M_U, 1, GL_FALSE, &M[0][0]);
	glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(N_U, 1, GL_FALSE, &N[0][0]);

	/*glm::vec3 ltPos = glm::vec3(light0.getPosition().x, light0.getPosition().y, light0.getPosition().z);

	L_MV = glm::lookAt(ltPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	L_MVBP = L_BP*L_MV;
	//glUniformMatrix4fv(L_MVBP_U, 1, GL_FALSE, &L_MVBP[0][0]);

	//glm::mat4 shaderMat = L_MVBP*M; // new 
	glm::mat4 shaderMat = L_MVBP*M; // new 
	glUniformMatrix4fv(L_MVBP_U, 1, GL_FALSE, &shaderMat[0][0]);
	*/
	
	//pop();
}

void ProtoContext::push(){
	// push current transformation matrix onto stack
	//matrixStack.push(M);
	matrixStack.push(M);

}

// reset transformation matrix with stored matrix on stack
void ProtoContext::pop(){

	// reset current transformation matrix with one on top of stack
	//M = matrixStack.top();
	M = matrixStack.top();

	// pop transformation matrix off top of stack
	matrixStack.pop();

	// rebuild matrices and update on GPU
	concat();
}

