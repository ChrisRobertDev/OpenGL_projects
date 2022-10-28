#pragma once
#include <map>
#include <string>
#include <GL\glew.h>
#include <Box2D\Box2D.h>


#include "Shader.h"
#include "Texture2D.h"
#include "GameObject.h"

class DataManager
{
public:
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;
	static std::vector<GameObject> Objects;
	static b2World* world;
	
	static void LoadShader(const GLchar *Vfile,const GLchar *Ffile , const std::string name);
	static void LoadTexture(const GLchar *filename, const std::string name, glm::ivec2 dims = glm::ivec2(1,1));
	static Shader GetShader(const std::string name);
	static Texture2D GetTexture(const std::string name);

	
	static void addObject(Texture2D texture, glm::vec2 position, glm::vec2 scale, b2BodyType type = b2_dynamicBody);
	static void destroyObject(GLuint index);
	static GLuint findObject(std::string name);

	static void initWorld(glm::vec2 gravity);
	static void initGround();//temporary


	
};

