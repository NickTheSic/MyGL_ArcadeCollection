#include <FrameworkPCH.h>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::DrawTriangle() const
{
	GLfloat Vertices[] =
	{
		 0.0f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f
	};

	GLuint vbo;
	GLuint vao;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), &Vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLint loc = 0;
	glEnableVertexAttribArray(loc);

	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}


void Renderer::Draw(const Mesh& mesh) const
{
	glBindBuffer(GL_ARRAY_BUFFER, mesh.m_Vbo);
	glBindVertexArray(mesh.m_Vao);

	GLint loc = 0;
	glEnableVertexAttribArray(loc);

	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(mesh.PrimitiveType, 0, mesh.m_NumVerts);
}