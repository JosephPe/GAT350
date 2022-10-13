#pragma once
#include "Resource/ResourceManager.h"
#include "Renderer.h"

namespace anthemum
{

	class Shader : public Resource
	{
	public:
		~Shader();

		virtual bool Create(std::string name, ...) override;

	public:
		GLuint m_shader = 0;
	};
}

