#include "stdafx.h"
#include "Terrain.h"
#include "Transform.h"
#include "Shape.h"
#include "Material.h"
#include "StaticBody.h"

Terrain::Terrain(ECS& ecs,std::string texture, glm::vec2 position, glm::vec2 scale, std::string filepath):
	e(ecs.eManager.addEntity())
{
	std::vector<b2Vec2> lines;
	std::vector<std::vector<GLint>> indexes;

	std::string filter;
	std::string line;
	std::ifstream input(filepath);

	while (std::getline(input, line)) {

		std::vector<GLint> row;
		std::stringstream ss(line);
		ss >> filter;
		if (filter == "Tile") {
			GLint x;
			while (ss >> x) {
				row.push_back(x);

			}
			indexes.push_back(row);
		}
		if (filter == "Hitbox") {
			b2Vec2 v;
			ss >> v.x >> v.y;
			lines.push_back(v);
		}

	}
	//still needs work
	e.addComponent<Transform>(position, scale);
	e.addComponent<Material>(DataManager::GetTexture(texture));
	e.addComponent<Shape>(indexes);
	e.setRenderable(true);
	e.addComponent<StaticBody>(position, lines);
}


Terrain::~Terrain()
{
}
