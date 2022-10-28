#pragma once
#include "ECS/ECS.h"
#include "DataManager.h"
class Terrain
{
private:
	Entity & e;

public:
	Terrain(ECS& ecs,std::string texture,glm::vec2 position,glm::vec2 scale, std::string filepath);
	~Terrain();
};

