#include "Mesh.h"

#include <sstream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<GLuint> indices)
{
	vertices_ = vertices;
	textures_ = textures;
	indices_ = indices;

	setupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
	vertices_ = vertices;
	indices_ = indices;
	setupMesh();
}

Mesh::Mesh()
{
}

void Mesh::Render(Shader* shader) {
	GLuint diffuseCount = 1;
	GLuint specularCount = 1;

	for (GLuint i = 0; i < textures_.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::stringstream ss;
		std::string number;
		std::string name = textures_[i].type;
		if (name == "texture_diffuse") 
			ss << diffuseCount++;
		else
			if (name == "texture_specular") 
				ss << specularCount++;
		number = ss.str();
		shader->SetInteger(("material" + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures_[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(vao_);
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	glGenBuffers(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* vertices_.size(), &vertices_[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint)* indices_.size(), &indices_[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}
