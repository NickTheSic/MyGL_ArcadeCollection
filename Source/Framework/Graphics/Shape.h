#pragma once
#include <Utilities/ColorList.h>

class Shape
{
	friend class Renderer;

public:
	Shape();
	~Shape();

	void Init(std::vector<glm::vec2>& points);
	void Init(std::vector<glm::vec2>& points, GLenum primitive);
	void Init(std::vector<glm::vec2>& points, const glm::vec3& col);
	void Init(std::vector<glm::vec2>& points, const glm::vec3& col, GLenum primitive);

	void MakeCircle(float radius, const glm::vec3& col, GLenum primitive = GL_LINE_LOOP);
	void MakeSqaure(float width, const glm::vec3& col, GLenum primitive = GL_LINE_LOOP);
	void MakeRectangle(float width, float height, const glm::vec3& col, GLenum primitive = GL_LINE_LOOP);

	void SetColor(const glm::vec3& col);
	void SetPrimitive(GLenum primitive);

protected:
	glm::vec3 m_Color;

	GLenum m_PrimitiveType;

	GLuint m_Vbo;
	GLuint m_Vao;
	GLuint m_NumVerts;
};

