#pragma once
#include "Resource/Resource.h" 
#include "Math/MathUtils.h" 
#include <vector> 
#include <memory> 

namespace anthemum
{
	class Texture;
	class Program;

	class Material : public Resource
	{
	public:
		virtual bool Create(std::string filename, ...) override;

		void Bind();

		std::shared_ptr<Program> GetProgram() { return m_program; }

	public:
		glm::vec3 color;
		//glm::vec3 diffuse;
		//glm::vec3 specular;
		float shininess = 0;
		glm::vec2 uv_tiling{ 1, 1};
		glm::vec2 uv_offset{ 0, 1};

	private:
		std::shared_ptr<Program> m_program;
		std::vector<std::shared_ptr<Texture>> m_textures;
	};
}