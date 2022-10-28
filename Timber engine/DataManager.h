#pragma once
#include "Shader.h"
#include "Texture2D.h"

class DataManager
{
public:
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;
	//static std::vector<GameObject> Objects;
	static b2World* world;
	
	static void LoadShader(const GLchar *Vfile,const GLchar *Ffile , const std::string name);
	static void LoadTexture(const GLchar *filename, const std::string name, glm::ivec2 dims = glm::ivec2(1,1));
	static Shader GetShader(const std::string name);
	static Texture2D GetTexture(const std::string name);

	
	static void addObject(Texture2D texture, glm::vec2 position, glm::vec2 scale, b2BodyType type = b2_dynamicBody,GLuint texIndex = 0);
	static void destroyObject(GLuint index);
	static GLuint findObject(glm::vec2 position);
	static GLboolean Exists(glm::vec2 position);

	static void initWorld(glm::vec2 gravity);
	static void initGround();//temporary


	
};

