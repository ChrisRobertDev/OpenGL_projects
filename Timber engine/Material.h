#pragma once
#include "ECS/ECS.h"
#include "Texture2D.h"

class Material : public Component
{
private:
	GLuint layer;
	Texture2D texture;
	glm::vec3 color;
public:
	Material(Texture2D texture, GLuint layer = 0, glm::vec3 color = glm::vec3(0.0f));
	~Material();

	void setTextureIndex(GLuint index) { texture.setIndex(index); }
	void setMirrorFlag(GLfloat flag) { texture.setMirrorFlag(flag); }

	GLuint getLayer() { return layer;}
	void Bind() { texture.Bind();}
	glm::vec4 getUVs() { return texture.getUVs(); }
	glm::vec4 getUVs(GLuint index) { return texture.getUVs(index); }
	GLfloat getMirrorFlag() { return texture.getMirrorFlag(); }

};

