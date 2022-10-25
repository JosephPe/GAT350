#include "Engine.h"
#include <iostream>

float vertices[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
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

	std::shared_ptr<anthemum::VertexBuffer> vb = anthemum::g_resourceManager.Get<anthemum::VertexBuffer>("box");
	vb->CreateVertexBuffer(sizeof(vertices), 36, vertices);
	vb->SetAttribute(0, 3, 8 * sizeof(float), 0);
	vb->SetAttribute(1, 3, 8 * sizeof(float), 3*sizeof(float));
	vb->SetAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));

	// 
	//GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vs, 1, &vertex_shader, NULL);
	//glCompileShader(vs);
	//GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fs, 1, &fragment_shader, NULL);
	//glCompileShader(fs);

	// create material 
	std::shared_ptr<anthemum::Material> material = anthemum::g_resourceManager.Get<anthemum::Material>("materials/box.mtrl");
	material->Bind();

	material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });
	material->GetProgram()->SetUniform("scale", 0.5f);

	//material->GetProgram()->SetUniform("scale", std::sin(anthemum::g_time.time * 3));

	glm::mat4 model{ 1 };
	glm::mat4 projection = glm::perspective(45.0f, anthemum::g_renderer.GetWidth() / (float)anthemum::g_renderer.GetHeight(), 0.01f, 100.0f);
	glm::vec3 cameraPosition = glm::vec3{ 0, 0, 2 };


		// 1 0 0 0
		// 1 1 0 0
		// 1 0 1 0
		// 1 0 0 1

	
		model = glm::scale(glm::vec3{ 0.5, 0.5, 0.5});
		float speed = 3;

		std::vector<anthemum::Transform> transforms;
		for (size_t i = 0; i < 100; i++)
		{
			transforms.push_back({ glm::vec3{ anthemum::randomf(-5, 5), anthemum::randomf(-5, 5), anthemum::randomf(-5, 5)}, glm::vec3{ anthemum::randomf(360), anthemum::randomf(360), anthemum::randomf(360)} });
		}

		//anthemum::Transform transforms[] =
		//{
		//	{ {0, 0, 0 }, { 0, 90, 0 } },
		//	{ {1, 0, 0 }, { 0, 90, 30 } },
		//	{ {2, 0, -1 }, { 0, 90, 0 } },
		//	{ {1, 0, 1 }, { 0, 90, 60 } },
		//};

		bool quit = false;
		while (!quit)
		{
			anthemum::Engine::Instance().Update();
			if (anthemum::g_inputSystem.GetKeyState(anthemum::key_escape) == anthemum::InputSystem::keyState::Pressed) quit = true;

			if (anthemum::g_inputSystem.GetKeyState(anthemum::key_a) == anthemum::InputSystem::keyState::held) cameraPosition.x -= speed * anthemum::g_time.deltaTime;
			if (anthemum::g_inputSystem.GetKeyState(anthemum::key_d) == anthemum::InputSystem::keyState::held) cameraPosition.x += speed * anthemum::g_time.deltaTime;
			if (anthemum::g_inputSystem.GetKeyState(anthemum::key_w) == anthemum::InputSystem::keyState::held) cameraPosition.y += speed * anthemum::g_time.deltaTime;
			if (anthemum::g_inputSystem.GetKeyState(anthemum::key_s) == anthemum::InputSystem::keyState::held) cameraPosition.y -= speed * anthemum::g_time.deltaTime;

			glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{0, 1, 0});

			//add input ot move camera

			//glm::mat4 mvp = projection * view * model;

			//model = glm::eulerAngleXYZ(0.0f, anthemum::g_time.time, 0.0f);
			//program->SetUniform("scale", std::sin(anthemum::g_time.time * 3));
			//program->SetUniform("transform", mx);
			//mx = glm::eulerAngleXYZ(0, 0, 1);
			anthemum::g_renderer.BeginFrame();

			for (size_t i = 0; i < transforms.size(); i++)
			{
				transforms[i].rotation += glm::vec3{ 0, 90 * anthemum::g_time.deltaTime, 0 };
				glm::mat4 mvp = projection * view * (glm::mat4)transforms[i];
				material->GetProgram()->SetUniform("mvp", mvp);
				vb->Draw();
			}

			//vb->Draw();

			anthemum::g_renderer.EndFrame();
		}

		anthemum::Engine::Instance().Shutdown();

		return 0;
}