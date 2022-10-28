#pragma once
#include "ECS/ECS.h"
#include "ECS/Array.h"
enum ShapeType {
	TILE,
	PLATFORM,
	GROUND_FLAT,
	GROUND_
};


class Shape :
	public Component
{
	ShapeType shape;
	
public:
	std::vector<std::vector<GLint>> textureIndexes;
	Shape(ShapeType shape = TILE);
	Shape(const std::vector<std::vector<GLint>> &arr);
	Shape(const std::string filepath, ShapeType shape = TILE);
	
	std::vector<std::vector<GLint>>& getTextureIndexes() { return textureIndexes; }
	~Shape();
};

