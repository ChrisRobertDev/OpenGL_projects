#include "stdafx.h"
#include "RendererSystem.h"
#include "Transform.h"
#include "CameraSystem.h"
#include "Shape.h"
//#include <iostream>


RendererSystem::RendererSystem(Shader shader, Shader debugShader):
	shader(shader),
	debugShader(debugShader),
	debugFlag(true)
{
	quad = new Quad();
	dQuad = new DebugQuad();
	circle = new Circle();
}


RendererSystem::~RendererSystem()
{
}



void RendererSystem::render()
{
	/*for(GLuint i = 0;i<MAX_LAYERS;i++)
		if(!renderingLayers[i].empty())
			for (auto&c : renderingLayers[i]) {
				shader.Use();
				if (c->entity->hasComponent<Transform>())
					shader.SetMatrix4("model", c->entity->getComponent<Transform>().getModelMatrix());
				else
					shader.SetMatrix4("model", glm::mat4(1.0f));

				this->shader.SetVector4f("texUvoffset", c->getUVs());
				if (0);
				else
					this->shader.SetFloat("isMirrored", 0.0f);

				c->Bind();
				quad->render();
			}*/

	for (auto&c : eManager->entities) {
		if(c->isRenderable())
			if (c->hasComponent<Shape>()) {
				glm::vec2 position = c->getComponent<Transform>().getPosition();
				GLfloat scale = c->getComponent<Transform>().getScale().x;
				glm::vec2 posCopy = glm::vec2(position.x + scale/2.0f,position.y-scale/2.0f);
				shader.Use();
				c->getComponent<Material>().Bind();
				this->shader.SetFloat("isMirrored", 0.0f);
				std::vector<std::vector<GLint>> arr = c->getComponent<Shape>().getTextureIndexes();

				for (GLuint i = 0; i < arr.size(); i++) {
					for (GLuint j = 0; j < arr[i].size(); j++) {
						if (arr[i][j] >= 0) {
							c->getComponent<Transform>().setPosition(posCopy);
							shader.SetMatrix4("model", c->getComponent<Transform>().getModelMatrix());
							this->shader.SetVector4f("texUvoffset", c->getComponent<Material>().getUVs(arr[i][j]));
							quad->render();
							posCopy.x += scale;
						}
						else {
							posCopy.x += scale;
						}
					}
					posCopy.y -= scale;
					posCopy.x = position.x + scale / 2.0f;
				}
				c->getComponent<Transform>().setPosition(position);
			}
			else
			{
				shader.Use();
				if (c->hasComponent<Transform>())
					shader.SetMatrix4("model", c->getComponent<Transform>().getModelMatrix());
				else
					shader.SetMatrix4("model", glm::mat4(1.0f));

				this->shader.SetVector4f("texUvoffset", c->getComponent<Material>().getUVs());

				this->shader.SetFloat("isMirrored", c->getComponent<Material>().getMirrorFlag());


				c->getComponent<Material>().Bind();
				quad->render();

				this->shader.SetFloat("isMirrored", 0.0f);
			}

	}

	if (debugFlag) {

	}
	//renderingLayers->clear();
}

void RendererSystem::preUpdate(GLfloat deltatime)
{
	if (sManager->hasSystem<CameraSystem>()) {
		shader.Use().SetMatrix4("projection", sManager->getSystem<CameraSystem>().getProjectionMatrix(), true);
	}
}
