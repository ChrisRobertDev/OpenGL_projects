#include "Plane.h"

#include <glm\gtc\matrix_transform.hpp>

Plane::Plane(GLuint amount, GLfloat offset, std::string filePath, bool hasNoise) :
	projection_(glm::mat4(1.0f)),
	view_(glm::mat4(1.0f)),
	position_(glm::vec3(0.0f)),
	scale_(glm::vec3(1.0f)),
	ambient_(glm::vec3(0.3f)),
	diffuse_(glm::vec3(0.7f)),
	specular_(glm::vec3(1.0f)),
	shininess_(128.0f)
	
{
	amount_ = amount;
	offset_ = offset;
	
	diffuseTex_ = Texture2D(filePath.c_str());

	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> normals;
	std::vector<std::vector<glm::vec3>> vertices;
	std::vector<glm::vec3> linedVerts;
	
	if (hasNoise) {
		//Random seed
		Noise* n;
		n = new Noise(amount, 49837461);
		n->computeArray(1.0f, 1.0f, 1.0f, 1.0f);
		//n->Smooth(0.7021f);
		n->Smooth(0.22616f);
		//n->Smooth(0.1195f);
		//Compute Vertices
		GLfloat zDistance = -(amount_ / 2.0f)*offset_;
		for (GLuint i = 0; i < amount; i++) {
			GLfloat xDistance = -(amount_ / 2.0f) * offset_;
			std::vector<glm::vec3> vert;
			for (GLuint j = 0; j < amount; j++) {
				GLfloat y = (n->getArrayIndex(i, j) + 1.0f)  * 32.0f - 32.0f;
				vert.push_back(glm::vec3(xDistance, y, zDistance));
				linedVerts.push_back(glm::vec3(xDistance, y, zDistance));
				xDistance += offset_;
			}
			vertices.push_back(vert);
			zDistance += offset_;
		}
	}
	else
	{
		GLfloat zDistance = -(amount_ / 2.0f)*offset_;
		for (GLuint i = 0; i < amount; i++) {
			GLfloat xDistance = -(amount_ / 2.0f) * offset_;
			std::vector<glm::vec3> vert;
			for (GLuint j = 0; j < amount; j++) {
				GLfloat y = 0.0f;
				vert.push_back(glm::vec3(xDistance, y, zDistance));
				linedVerts.push_back(glm::vec3(xDistance, y, zDistance));
				xDistance += offset_;
			}
			vertices.push_back(vert);
			zDistance += offset_;
		}
	}
	
	//Compute indices
	for (GLuint i = 0; i < amount_-1; i++) {
		for (GLuint j = 0; j < amount_-1; j++) {
			indices_.push_back(i*amount_ + j);
			indices_.push_back(i*amount_ + j + 1);
			indices_.push_back((i + 1) * amount_ + j);
			
			indices_.push_back((i + 1) * amount_ + j);
			indices_.push_back(i * amount_ + j + 1);
			indices_.push_back((i + 1) * amount_ + j + 1);
		}
	}


	//Compute texture Coords
	for (GLuint i = 0; i < amount_; i++) {
		for (GLuint j = 0; j < amount_; j++) {
			if (i % 2 == 0 && j % 2 == 0) {
				uv.push_back(glm::vec2(0.0f,1.0f));
			}
			if (i % 2 == 0 && j % 2 == 1) {
				uv.push_back(glm::vec2(1.0f, 1.0f));
			}
			if (i % 2 == 1 && j % 2 == 0) {
				uv.push_back(glm::vec2(0.0f, 0.0f));
			}
			if (i % 2 == 1 && j % 2 == 1) {
				uv.push_back(glm::vec2(1.0f, 0.0f));
			}
			
		}
	}

	//Compute normals
	for (GLuint i = 0; i < amount_; i++) {
		for (GLuint j = 0; j < amount_; j++) {
			glm::vec3 v = vertices[i][j];
			if (i == 0) {
				if (j == 0) {
					glm::vec3 n1 = glm::normalize(glm::cross(vertices[i + 1][j] - v, vertices[i + 1][j + 1] - v));
					glm::vec3 n2 = glm::normalize(glm::cross(vertices[i + 1][j + 1] - v, vertices[i][j + 1] - v));
					normals.push_back(glm::normalize(n1 + n2));
				}
				else
					if (j == amount_ - 1) {
						glm::vec3 n1 = glm::normalize(glm::cross(vertices[i][j - 1] - v, vertices[i + 1][j] - v));
						normals.push_back(glm::normalize(n1));
					}
					else
					{
						glm::vec3 n1 = glm::normalize(glm::cross(vertices[i][j - 1] - v, vertices[i + 1][j] - v));
						glm::vec3 n2 = glm::normalize(glm::cross(vertices[i + 1][j] - v, vertices[i + 1][j + 1] - v));
						glm::vec3 n3 = glm::normalize(glm::cross(vertices[i + 1][j + 1] - v, vertices[i][j + 1] - v));
						normals.push_back(glm::normalize(n1 + n2 + n3));
					}
			}
			else
				if (i == amount_ - 1) {
					if (j == 0) {
						glm::vec3 n1 = glm::normalize(glm::cross(vertices[i][j + 1] - v, vertices[i - 1][j] - v));
						normals.push_back(glm::normalize(n1));
					}
					else
						if (j == amount_ - 1) {
							glm::vec3 n1 = glm::normalize(glm::cross(vertices[i - 1][j] - v, vertices[i - 1][j - 1] - v));
							glm::vec3 n2 = glm::normalize(glm::cross(vertices[i - 1][j - 1] - v, vertices[i][j - 1] - v));
							normals.push_back(glm::normalize(n1 + n2));
						}
						else
						{
							glm::vec3 n1 = glm::normalize(glm::cross(vertices[i - 1][j - 1] - v, vertices[i][j - 1] - v));
							glm::vec3 n2 = glm::normalize(glm::cross(vertices[i - 1][j] - v, vertices[i - 1][j - 1] - v));
							glm::vec3 n3 = glm::normalize(glm::cross(vertices[i][j + 1] - v, vertices[i - 1][j] - v));
							normals.push_back(glm::normalize(n1 + n2 + n3));
						}
				}
				else
					if (j == 0 ) {
						glm::vec3 n1 = glm::normalize(glm::cross(vertices[i + 1][j] - v, vertices[i + 1][j + 1] - v));
						glm::vec3 n2 = glm::normalize(glm::cross(vertices[i + 1][j + 1] - v, vertices[i][j + 1] - v));
						glm::vec3 n3 = glm::normalize(glm::cross(vertices[i][j + 1] - v, vertices[i - 1][j] - v));
						normals.push_back(glm::normalize(n1 + n2 + n3));
					}
					else
						if (j == amount - 1) {
							glm::vec3 n1 = glm::normalize(glm::cross(vertices[i - 1][j] - v, vertices[i - 1][j - 1] - v));
							glm::vec3 n2 = glm::normalize(glm::cross(vertices[i - 1][j - 1] - v, vertices[i][j - 1] - v));
							glm::vec3 n3 = glm::normalize(glm::cross(vertices[i][j - 1] - v, vertices[i + 1][j] - v));
							normals.push_back(glm::normalize(n1 + n2 + n3));
						}
						else
						{
							glm::vec3 n1 = -glm::normalize(glm::cross(vertices[i - 1][j] - v, vertices[i - 1][j + 1] - v));
							glm::vec3 n2 = -glm::normalize(glm::cross(vertices[i - 1][j + 1] - v, vertices[i][j + 1] - v));
							glm::vec3 n3 = -glm::normalize(glm::cross(vertices[i][j + 1] - v, vertices[i + 1][j + 1] - v));
							glm::vec3 n4 = -glm::normalize(glm::cross(vertices[i + 1][j + 1] - v, vertices[i + 1][j] - v));
							glm::vec3 n5 = -glm::normalize(glm::cross(vertices[i + 1][j] - v, vertices[i + 1][j - 1] - v));
							glm::vec3 n6 = -glm::normalize(glm::cross(vertices[i + 1][j - 1] - v, vertices[i][j - 1] - v));
							glm::vec3 n7 = -glm::normalize(glm::cross(vertices[i][j - 1] - v, vertices[i - 1][j - 1] - v));
							glm::vec3 n8 = -glm::normalize(glm::cross(vertices[i - 1][j - 1] - v, vertices[i - 1][j] - v));
							normals.push_back(glm::normalize(n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8));
						}
		}
	}

	//Transfer data to Vertex
	
	for (GLuint i = 0; i < amount*amount; i++) {
		Vertex v;
		v.position = linedVerts[i];
		v.normal = normals[i];
		v.uv = uv[i];
		vertices_.push_back(v);
	}


	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* vertices_.size(), &vertices_[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* indices_.size(), &indices_[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}


Plane::~Plane()
{
}

void Plane::Render(Shader* shader) {

	glm::mat4 model(1.0f);

	model = glm::translate(model, position_);
	shader->Use();
	shader->SetMatrix4("projection", projection_);
	shader->SetMatrix4("view", view_);
	shader->SetMatrix4("model", model);

	shader->SetInteger("material.diffuse", 0);
	shader->SetFloat("material.shininess", shininess_);


	shader->SetFloat3("light.position", lightPosition_);
	shader->SetFloat3("light.ambient", ambient_);
	shader->SetFloat3("light.diffuse", diffuse_);
	shader->SetFloat3("light.specular", specular_);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTex_.getID());

	glBindVertexArray(vao_);
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void Plane::setProjection(glm::mat4 projection)
{
	projection_ = projection;
}

void Plane::setView(glm::mat4 view)
{
	view_ = view;
}

void Plane::setPosition(glm::vec3 position)
{
	position_ = position;
}

void Plane::setLightDirection(glm::vec3 direction) {
	lightPosition_ = direction;
}

