#include "Program.h"
#include "Engine.h"

namespace anthemum
{
	Program::~Program()
	{
		if (m_program)
		{
			glDeleteProgram(m_program);
		}
	}

	bool Program::Create(std::string filename, ...)
	{
		rapidjson::Document document;
		bool success = anthemum::json::Load(filename, document);
		if (!success)
		{

			LOG("Could not load program file (%s).", filename.c_str());
			return false;
		}

		// create program 
		m_program = glCreateProgram();

		// get/add vertex shader 
		std::string vertex_shader;
		READ_DATA(document, vertex_shader);
		if (!vertex_shader.empty())
		{

			auto vshader = g_resourceManager.Get<anthemum::Shader>(vertex_shader, GL_VERTEX_SHADER);
			AddShader(vshader);
		}

		// get/add fragment shader 
		std::string fragment_shader;
		READ_DATA(document, fragment_shader);
		if (!fragment_shader.empty())
		{

			auto fshader = g_resourceManager.Get<anthemum::Shader>(fragment_shader, (void*)GL_FRAGMENT_SHADER);
			AddShader(fshader);
		}
		Link();

		return true;
	}

	void Program::AddShader(const std::shared_ptr<Shader>& shader)
	{
		m_shader.push_back(shader);

		glAttachShader(m_program, shader->m_shader);
	}

	void Program::Link()
	{
		// link shader programs 
		glLinkProgram(m_program);

		// check program link status 
		GLint status;
		glGetProgramiv(m_program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint length = 0;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);

			if (length > 0)
			{
				std::string infoLog(length, ' ');

				glGetProgramInfoLog(m_program, length, &length, &infoLog[0]);

				LOG("Failed to link program.");
				LOG("Program Info: %s", infoLog.c_str());
			}

			glDeleteProgram(m_program);
			m_program = 0;
		}
	}

	void Program::Use()
	{
		glUseProgram(m_program);
	}

	void Program::SetUniform(const std::string& name, float value)
	{
		GLint uniform = GetUniform(name);
		if (uniform != -1) glUniform1f(uniform, value);
	}

	void Program::SetUniform(const std::string& name, const glm::vec3& value)
	{
		GLint uniform = GetUniform(name);
		if (uniform != -1) glUniform3fv(uniform, 1, &value[0]);
	}

	void Program::SetUniform(const std::string& name, const glm::mat4& value)
	{
		GLint uniform = GetUniform(name);
		if (uniform != -1)
			glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Program::SetUniform(const std::string& name, int value)
	{
		GLint glUniform1i;
		GLint v0;
	}

	void Program::SetUniform(const std::string& name, unsigned int value)
	{
		GLint glUniform1f;
		GLfloat v0;
	}

	void Program::SetUniform(const std::string& name, bool value)
	{
	}

	void Program::SetUniform(const std::string& name, const glm::vec2& value)
	{
	}

	void Program::SetUniform(const std::string& name, const glm::vec4& value)
	{
	}

	void Program::SetUniform(const std::string& name, const glm::mat3& value)
	{
	}

	GLint Program::GetUniform(const std::string& name)
	{
		// find uniform in map 
		auto uniform = m_uniform.find(name);
		// if not found, get uniform in program 
		if (uniform == m_uniform.end())
		{
			// get uniform in program 

			GLint location = glGetUniformLocation(m_program, name.c_str());
			if (location == -1)
			{

				LOG("Could not find uniform location: %s", name.c_str());
			}
			m_uniform[name] = location;
		}

		return m_uniform[name];
	}
}