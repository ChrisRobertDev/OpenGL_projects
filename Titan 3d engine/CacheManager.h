#pragma once
#include <vector>
#include <map>
#include "Shader.h"
#include "Cube.h"
#include "Model.h"


class CacheManager
{
public:
	
	static void renderCache();

	// add object Functions

	static void addShader(const std::string* name, const std::string* vPath, const std::string* fPath);
	//static void addTexture(const std::string* name);
	//static void addObject(); /// WORK IN PROGRESS
	static void addTerrain(const std::string* name, const std::string* filePath);
	static void addModel(const std::string* name, const std::string* filePath);
	// delete object Functions
	static void deleteShader(const std::string* name);
	static void deleteTerrain(const std::string* name);
	static void deleteModel(const std::string* name);
	// getters
	static Shader* getShader(const std::string* name);

private:
	//shaders
	static std::map<std::string, Shader*> shaderCache_;
	//textures
	///.... WORK IN PROGRESS
	//Rendering objects
	static std::vector<Cube*> renderObjectsCache_;
	
	static std::map<std::string, Model*> terrainCache_;

	static std::map<std::string, Model*> modelCache_;

	static std::vector<glm::vec3> lightsPositionCache_;

	CacheManager();
};

