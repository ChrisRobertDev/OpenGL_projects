#include "stdafx.h"
#include "Shape.h"


Shape::Shape(ShapeType shape):
	shape(shape)
{
	std::vector<GLint> ar;
	ar.emplace_back(0);
	textureIndexes.emplace_back(ar);
}

Shape::Shape(const std::vector<std::vector<GLint>>& arr)
{
	textureIndexes = arr;
	shape = TILE;
}

Shape::Shape(const std::string filepath, ShapeType shape):
	shape(shape)
{

	std::string line;
	std::ifstream input(filepath);

	while (std::getline(input, line)) {
		GLint x;
		std::vector<GLint> row;
		std::stringstream ss(line);
		while (ss >> x) {
			row.push_back(x);

		}
		this->textureIndexes.push_back(row);
	}
}


Shape::~Shape()
{
}
