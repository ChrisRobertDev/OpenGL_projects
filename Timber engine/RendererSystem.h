#pragma once
#include "ECS/ECS.h"
#include "Shader.h"
#include "Polygons.h"
#include "Material.h"
#include <deque>

#define MAX_LAYERS 4

class RendererSystem : public System
{
private:
	Shader shader;
	Shader debugShader;
	GLboolean debugFlag;

	// Polygons
	Quad* quad;
	DebugQuad* dQuad;
	Circle* circle;
	
public:
	RendererSystem(Shader shader,Shader debugShader);
	~RendererSystem();

	void render() override;
	void preUpdate(GLfloat deltatime) override;
	
};

