#include "Cube.h"

#include <glm\gtx\quaternion.hpp>

Cube::Cube(const GLchar* diffusePath, const GLchar* specularPath):
	position_(glm::vec3(0.0f)),
	scale_(glm::vec3(1.0f)),
	cubeColor_(glm::vec3(1.0f)),
	ambient_(glm::vec3(0.2f)),
	diffuse_(glm::vec3(0.5f)),
	specular_(glm::vec3(1.0f)),
	shininess_(128.0f),
	lightAmbient_(glm::vec3(0.3f)),
	lightDiffuse_(glm::vec3(0.7f)),
	lightSpecular_(glm::vec3(1.0f))
{
	
	loadTexture(diffusePath, specularPath);


	GLfloat vertices[] = {
		
		// Back face
		- 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f,-1.0f,// Bottom-left
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f, 0.0f,-1.0f,// top-right
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f, 0.0f,-1.0f,// bottom-right         
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f, 0.0f,-1.0f,// top-right
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f,-1.0f,// bottom-left
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f,-1.0f,// top-left
		 // Front face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f,1.0f,// bottom-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f,1.0f,// bottom-right
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f,1.0f,// top-right
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f,1.0f,// top-right
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f,1.0f,// top-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f,1.0f,// bottom-left
		// Left face
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f,0.0f,// top-right
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f, 0.0f,0.0f,// top-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f,0.0f,// bottom-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f,0.0f,// bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f, 0.0f,0.0f,// bottom-right
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f,0.0f,// top-right
		// Right face
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f,0.0f,// top-left
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f,0.0f,// bottom-right
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f,0.0f,// top-right         
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f,0.0f,// bottom-right
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f,0.0f,// top-left
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f,0.0f,// bottom-left     
		// Bottom face
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,0.0f,// top-right
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,0.0f,// top-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,0.0f,// bottom-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,0.0f,// bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,0.0f,// bottom-right
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,0.0f,// top-right
		// Top face
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,0.0f,// top-left
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f,0.0f,// bottom-right
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 1.0f,0.0f,// top-right     
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f,0.0f,// bottom-right
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,0.0f,// top-left
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f,0.0f// bottom-left 
	};



	GLuint vbo;

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Normals attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

}


Cube::~Cube()
{
}

void Cube::Render(Shader* shader)
{
	//prepare position rotation scale
	glm::mat4 model;
	model = glm::translate(glm::mat4(), position_);
	//work in progress but for now glm::rotate should do
	//model = glm::rotate(model,glm::radians(angle), rotation);
	model = model*rotation_;
	model = glm::scale(model, scale_);

	//uniforms
	shader->Use();
	shader->SetMatrix4("projection", projection_);
	shader->SetMatrix4("view", view_);
	shader->SetMatrix4("model", model);
	//shader->SetFloat3("cubeColor", cubeColor_);
	//shader->SetFloat3("lightColor", lightColor_);
	//shader->SetFloat3("lightPosition",);
	shader->SetFloat3("viewPosition", viewPosition_);

	//shader->SetFloat3("material.ambient", ambient_);
	//shader->SetFloat3("material.diffuse", diffuse_);
	//shader->SetFloat3("material.specular", specular_);
	//shader->SetInteger("material.diffuse", 0);
	shader->SetInteger("material.specular", 1);
	shader->SetFloat("material.shininess", shininess_);


	shader->SetFloat3("light.position", lightPosition_);
	shader->SetFloat3("light.ambient", lightAmbient_);
	shader->SetFloat3("light.diffuse", lightDiffuse_);
	shader->SetFloat3("light.specular", lightSpecular_);
	//bind texture if it has been loaded
	
	
	if (textureDiffuse_ != 0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureDiffuse_);
	}

	if (textureSpecular_ != 0) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureSpecular_);
	}
	//draw the figure
	glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Cube::setProjection(glm::mat4 projection)
{
	projection_ = projection;
}

void Cube::setView(glm::mat4 view)
{
	view_ = view;
}

void Cube::setPosition(glm::vec3 position)
{
	position_ = position;
}

void Cube::setRotation(GLfloat yaw,GLfloat pitch, GLfloat roll) {
	//glm::mat4 rot(1.0f);
	//if (pitch != 0.0f)
	//	rot = Rotate(pitch, glm::vec3(1.0f, 0.0f, 0.0f))*rot;
	//if (yaw != 0.0f)
	//	rot = Rotate(yaw, glm::vec3(0.0f, 1.0f, 0.0f)) * rot;
	//
	//rotation_ = rot;
	
	

	//Still getting Gimbal lock
	yaw = -yaw;
	pitch = -pitch;
	roll = -roll;

	glm::quat q,r,s;
	q.x = glm::sin(glm::radians(pitch) / 2.0f);
	q.y = 0.0f;
	q.z = 0.0f;
	q.w = glm::cos(glm::radians(pitch) / 2.0f);

	r.x = 0.0f;
	r.y = glm::sin(glm::radians(yaw) / 2.0f);
	r.z = 0.0f;
	r.w = glm::cos(glm::radians(yaw) / 2.0f);

	s.x = 0.0f;
	s.y = 0.0f;
	s.z = glm::sin(glm::radians(roll) / 2.0f);
	s.w = glm::cos(glm::radians(roll) / 2.0f);

	rotation_ = glm::mat4_cast(q*r*s);
}

void Cube::setScale(glm::vec3 scale)
{
	scale_ = scale;
}

void Cube::setViewPosition(const glm::vec3 position)
{
	viewPosition_ = position;
}

void Cube::setLightPosition(const glm::vec3 position)
{
	lightPosition_ = position;
}

void Cube::setCubeColor(const glm::vec3 color)
{
	cubeColor_ = color;
}

void Cube::setLightColor(const glm::vec3 color)
{
	lightColor_ = color;
}

glm::vec3 Cube::getPosition()
{
	return position_;
}

void Cube::loadTexture(const GLchar* diffusePath, const GLchar* specularPath)
{
	//diffuse
	if (diffusePath != nullptr) {
		int width, height;
		unsigned char* image = SOIL_load_image(diffusePath, &width, &height, 0, SOIL_LOAD_RGB);

		glGenTextures(1, &textureDiffuse_);
		glBindTexture(GL_TEXTURE_2D, textureDiffuse_);

		// Set our texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	//specular
	if (specularPath != nullptr) {
		int width, height;
		unsigned char* image = SOIL_load_image(specularPath, &width, &height, 0, SOIL_LOAD_RGB);

		glGenTextures(1, &textureSpecular_);
		glBindTexture(GL_TEXTURE_2D, textureSpecular_);

		// Set our texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

glm::vec3 Cube::RotateV3(GLfloat theta, glm::vec3 Axis) {
	glm::quat p;
	p.x = position_.x;
	p.y = position_.y;
	p.z = position_.z;
	p.w = 0.0f;
	glm::quat q;

	q.x = Axis.x*glm::sin(glm::radians(theta) / 2.0f);
	q.y = Axis.y*glm::sin(glm::radians(theta) / 2.0f);
	q.z = Axis.z*glm::sin(glm::radians(theta) / 2.0f);
	q.w = glm::cos(glm::radians(theta) / 2.0f);
	glm::quat R = q * p * glm::conjugate(q);
	return glm::vec3(R.x, R.y, R.z);
}

glm::mat4 Cube::Rotate(GLfloat theta, glm::vec3 Axis) {
	glm::quat p;
	p.x = position_.x;
	p.y = position_.y;
	p.z = position_.z;
	p.w = 0.0f;
	glm::quat q;

	q.x = Axis.x*glm::sin(glm::radians(theta) / 2.0f);
	q.y = Axis.y*glm::sin(glm::radians(theta) / 2.0f);
	q.z = Axis.z*glm::sin(glm::radians(theta) / 2.0f);
	q.w = glm::cos(glm::radians(theta) / 2.0f);
	glm::quat R = q * p * glm::conjugate(q);

	return glm::mat4_cast(R);
}