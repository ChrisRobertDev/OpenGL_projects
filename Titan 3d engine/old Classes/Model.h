#pragma once
#define ASSIMP_BUILD_BOOST_WORKAROUND

#include <string>
#include <vector>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"

class Model
{
public:
	Model(GLchar* path);

	void Render(Shader* shader);
private:
	std::vector<Mesh> meshes_;
	std::vector<Texture> loadedTextures_;
	std::string directory_;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh,const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* material,aiTextureType type,std::string typeName);
	GLint textureFromFile(const GLchar* path, std::string directory);
};

