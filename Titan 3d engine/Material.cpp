#include "Material.h"



Material::Material()
	
{
	ambient_ = glm::vec3(0.0f);
	diffuse_ = glm::vec3(0.0f);
	specular_ = glm::vec3(0.0f);
	shininess_ = 1.0f;
	dissolve_ = 1.0f;
	illumination_ = 2;
	name_ = nullptr;
}


Material::~Material()
{
}


void Material::Bind(Shader* shader)
{
	//bind Textures
	//for (GLuint i = 0; i < textures_.size(); i++) {
	//	textures_[i].Bind(shader);
	//}
		
	//bind the rest of the Materials
	
	shader->SetFloat("material.Ns", shininess_);
	shader->SetFloat3("material.Kd", diffuse_);
	shader->SetFloat3("material.Ka", ambient_);
	shader->SetFloat3("material.Ks", specular_);
	shader->SetFloat("material.d", dissolve_);
	shader->SetInteger("material.illum", illumination_);

}

//Adders
void Material::addTexture(const GLchar* path, TextureType type)
{
	Texture2D texture = Texture2D(path, type);
	textures_.push_back(texture);
}
//Setters
void Material::setMaterialAmbient(glm::vec3 ambient) {
	ambient_ = ambient;
}
void Material::setMaterialDiffuse(glm::vec3 diffuse) {
	diffuse_ = diffuse;
}
void Material::setMaterialSpecular(glm::vec3 specular) {
	specular_ = specular;
}
void Material::setMaterialShininess(GLfloat shininess) {
	shininess_ = shininess;
}
void Material::setMaterialDissolve(GLfloat dissolve) {
	dissolve_ = dissolve;
}
void Material::setMaterialIllumination(GLuint illumination) {
	illumination_ = illumination;
}
void Material::setMaterialName(const GLchar* name) {
	name_ = std::string(name);
}
//Getters
glm::vec3 Material::getMaterialAmbient() {
	return ambient_;
}
glm::vec3 Material::getMaterialDiffuse() {
	return diffuse_;
}

glm::vec3 Material::getMaterialSpecular() {
	return specular_;
}
GLfloat Material::getMaterialShininess() {
	return shininess_;
}
GLfloat Material::getMaterialDissolve() {
	return dissolve_;
}
GLuint Material::getMaterialIllumination() {
	return illumination_;
}
std::string Material::getMaterialName() {
	return name_;
}