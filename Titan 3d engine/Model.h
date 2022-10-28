#pragma once


#include <string>
#include <vector>

#include <GL\glew.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"

class Model
{
public:
	Model(std::string path);

	void Render(Shader* shader);

	//Setters
	void setShaderName(std::string name);

	//Getters
	std::string getShaderName();

private:
	std::vector<Mesh> meshes_;
	std::vector<Texture> loadedTextures_;
	std::string directory_;
	std::string shader_;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh,const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
	GLuint textureFromFile(const GLchar* path, std::string directory);
};

