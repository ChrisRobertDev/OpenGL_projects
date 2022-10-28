#pragma once
#include "stdafx.h"

class Polygon {
public:
	Polygon() {}

	virtual void render() = 0;

	virtual ~Polygon() {}

};

class Quad : public Polygon{
private:
	GLuint vao;
public:
	Quad() {
		GLfloat Vdata[] = {
			-0.5f,-0.5, 0.0f,0.0f,
			0.5f,-0.5,	1.0f,0.0f,
			0.5f,0.5,	1.0f,1.0f,

			-0.5f,-0.5,	0.0f,0.0f,
			-0.5f,0.5,	0.0f,1.0f,
			0.5f,0.5,	1.0f,1.0f
		};
		GLuint vbo;

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vao);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vdata), Vdata, GL_STATIC_DRAW);


		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);

		glBindBuffer(1, 0);
		glBindVertexArray(0);
	}
	~Quad() {

	}
	void render() override {
		glBindVertexArray(this->vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

};

class DebugQuad :public Polygon {
private:
	GLuint vao;
	GLuint ibo;
public:
	DebugQuad() {
		GLfloat Vdata2[] = {
			-0.5f, -0.5,
			0.5f, -0.5,
			-0.5f, 0.5,
			0.5f, 0.5
		};
		GLuint indices[] = {
			//0,1,3,  0,2,3
			0,1,3,2,0
		};


		GLuint vbo;

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vdata2), Vdata2, GL_STATIC_DRAW);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

		glBindBuffer(1, 0);
		glBindVertexArray(0);
	}
	~DebugQuad() {}
	void render() override {
		glBindVertexArray(this->vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};

class Circle :public Polygon {
private:
	GLuint vao;
	GLuint ibo;
public:
	Circle() {
		GLuint numberOfPoints = 100;

		std::vector<glm::vec2> v;
		std::vector<GLuint> ind;
		v.push_back(glm::vec2(0.0, 0.0));
		ind.push_back(0);

		for (GLuint i = 0; i < numberOfPoints; i++) {
			GLfloat angle = ((GLfloat)i / numberOfPoints) * 2 * glm::pi<GLfloat>();
			glm::vec2 a;
			a.x = glm::cos(angle)*0.5f;
			a.y = glm::sin(angle)*0.5f;
			v.push_back(a);
			ind.push_back(i + 1);
		}
		ind.push_back(ind[1]);

		GLuint circleVbo;
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &circleVbo);

		glBindBuffer(GL_ARRAY_BUFFER, circleVbo);
		glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(glm::vec2), &v[0], GL_STATIC_DRAW);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * sizeof(GLuint), &ind[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

		glBindBuffer(1, 0);
		glBindVertexArray(0);
	}
	~Circle() {}
	void render() override {
		glBindVertexArray(this->vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glDrawElements(GL_LINE_STRIP, 102, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};