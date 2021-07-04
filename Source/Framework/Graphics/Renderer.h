#pragma once

class FrameworkAPI Renderer
{
public:
	Renderer();
	~Renderer();

	void Init();

	void BeginDraw() const;
	void EndDraw() const;

	void Draw(const class Mesh&) const;

private:
	std::unique_ptr<ShaderProgram> m_Shader;

	std::unique_ptr<ShaderProgram> m_BatchShader;
};