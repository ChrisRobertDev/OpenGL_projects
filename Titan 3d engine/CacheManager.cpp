#include "CacheManager.h"

std::map<std::string, Shader*> CacheManager::shaderCache_;
std::vector<Cube*> CacheManager::renderObjectsCache_;

std::map<std::string, Model*> CacheManager::terrainCache_;
std::map<std::string, Model*> CacheManager::modelCache_;

std::vector<glm::vec3> CacheManager::lightsPositionCache_;

void CacheManager::renderCache()
{
	if (!renderObjectsCache_.empty()) {
		for (GLuint i = 0; i < renderObjectsCache_.size();i++) {
			//manage transformations or collision stuff
			/// WORK IN PROGRESS
			//draw Cubes
			renderObjectsCache_[i]->Render(getShader(&std::string("Cube")));
			
		}
	}
	
	if (!renderObjectsCache_.empty()) {
		for (GLuint i = 0; i < renderObjectsCache_.size(); i++) {
			//manage transformations or collision stuff
			/// WORK IN PROGRESS
			//draw Cubes
			renderObjectsCache_[i]->Render(getShader(&std::string("Cube")));

		}
	}
	if (!terrainCache_.empty()) {
		for (auto const& iter:terrainCache_) {
			//manage transformations or collision stuff
			/// WORK IN PROGRESS
			//draw terrains
			iter.second->Render(getShader(&iter.second->getShaderName()));

		}
	}

	if (!modelCache_.empty()) {
		for (auto const& iter : modelCache_) {
			//manage transformations or collision stuff
			/// WORK IN PROGRESS
			//draw Models
			iter.second->Render(getShader(&iter.second->getShaderName()));

		}
	}

}

void CacheManager::addShader(const std::string * name, const std::string * vPath, const std::string* fPath)
{
	Shader shader(vPath->c_str(), fPath->c_str());
	shaderCache_[name->c_str()] = &shader;
}

Shader* CacheManager::getShader(const std::string * name)
{
	return shaderCache_[name->c_str()];
}

void CacheManager::addTerrain(const std::string* name, const std::string* filePath) {
	Model* terrain;
	terrain = new Model(*filePath);
	terrainCache_[*name] = terrain;
	delete terrain;
}
void CacheManager::addModel(const std::string* name, const std::string* filePath) {
	Model* model;
	model = new Model(*filePath);
	modelCache_[*name] = model;
	delete model;
}

void CacheManager::deleteShader(const std::string* name) {
	shaderCache_.erase(*name);
}
void CacheManager::deleteTerrain(const std::string* name) {
	terrainCache_.erase(*name);
}
void CacheManager::deleteModel(const std::string* name) {
	modelCache_.erase(*name);
}

