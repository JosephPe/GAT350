#include "Engine.h"
#include <iostream>

float points[] = {
	-0.8f, -0.8f,  0.0f,
   0.8f,  0.8f,  0.0f,
   -0.8f, 0.8f,  0.0f,

  -0.8f, -0.8f,  0.0f,
   0.8f,  0.8f,  0.0f,
   0.8f, -0.8f,  0.0f
};

glm::vec3 colors[] =
{
	{0, 0, 1 },
	{1, 0, 1 },
	{1, 1, 1 },
	{0, 1, 0 },
	{0, 1, 1 },
	{1, 1, 0 },
};

glm::vec2 uV[]
{
	{ 0, 0},
	{ 1, 1},
	{ 0, 1},
	{ 0, 0},
	{ 1, 1},
	{ 1, 0}
};

int main(int argc, char** argv)
{
	LOG("Application Started...");
	anthemum::InitializeMemory();
		anthemum::SetFilePath("../Assets");

		anthemum::Engine::Instance().Initialize();
		anthemum::Engine::Instance().Register();
		LOG("Engine Initialized...");

 		anthemum::g_renderer.CreateWindow("Neumont", 800, 600, false);
		LOG("Window Initialized");
		// create vertex buffer
		GLuint pvbo = 0;
		glGenBuffers(1, &pvbo);
		glBindBuffer(GL_ARRAY_BUFFER, pvbo);
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

		GLuint cvbo = 0;
		glGenBuffers(1, &cvbo);
		glBindBuffer(GL_ARRAY_BUFFER, cvbo);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), colors, GL_STATIC_DRAW);

		GLuint tvbo = 0;
		glGenBuffers(1, &tvbo);
		glBindBuffer(GL_ARRAY_BUFFER, tvbo);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), uV, GL_STATIC_DRAW);

		// create vertex array
		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
			
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, pvbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, cvbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, tvbo);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		// create shader
		std::shared_ptr<anthemum::Shader> vs = anthemum::g_resourceManager.Get<anthemum::Shader>("shaders/basic.vert", GL_VERTEX_SHADER);
		std::shared_ptr<anthemum::Shader> fs = anthemum::g_resourceManager.Get<anthemum::Shader>("shaders/basic.frag", GL_FRAGMENT_SHADER);

		// 
		//GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		//glShaderSource(vs, 1, &vertex_shader, NULL);
		//glCompileShader(vs);
		//GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		//glShaderSource(fs, 1, &fragment_shader, NULL);
		//glCompileShader(fs);

		// create program
		GLuint program = glCreateProgram();
		glAttachShader(program, fs->m_shader);
		glAttachShader(program, vs->m_shader);
		glLinkProgram(program);
		glUseProgram(program);

		GLint uniform1 = glGetUniformLocation(program, "scale");
		GLint uniform2 = glGetUniformLocation(program, "tint");
		GLint uniform3 = glGetUniformLocation(program, "transform");

		glUniform3f(uniform2, 1, 0, 0);

		// 1 0 0 0
		// 1 1 0 0
		// 1 0 1 0
		// 1 0 0 1


		glm::mat4 mx{ 1 };
		//mx = glm::scale(glm::vec3{ 0.5, 0.5, 0.5});

		bool quit = false;
		while (!quit)
		{
			anthemum::Engine::Instance().Update();
			if (anthemum::g_inputSystem.GetKeyState(anthemum::key_escape) == anthemum::InputSystem::keyState::Pressed) quit = true;

			glUniform1f(uniform1, std::sin(anthemum::g_time.time));
			mx = glm::eulerAngleXYZ(0, 0, 1);
			glUniformMatrix4fv(uniform3, 1, GL_FALSE, glm::value_ptr(mx));
			anthemum::g_renderer.BeginFrame();

			glDrawArrays(GL_TRIANGLES, 0, 6);

			anthemum::g_renderer.EndFrame();
		}

		anthemum::Engine::Instance().Shutdown();

		return 0;
}