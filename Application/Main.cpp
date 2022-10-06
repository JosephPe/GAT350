#include "Engine.h"
#include <iostream>

int main()
{
	
		anthemum::InitializeMemory();

		anthemum::Engine::Instance().Initialize();
		anthemum::Engine::Instance().Register();

		anthemum::g_renderer.CreateWindow("Neumont", 800, 600);

		bool quit = false;
		while (!quit)
		{
			anthemum::Engine::Instance().Update();

			if (anthemum::g_inputSystem.GetKeyState(anthemum::key_escape) == anthemum::InputSystem::keyState::Pressed) quit = true;

			

			anthemum::g_renderer.BeginFrame();
			anthemum::g_renderer.EndFrame();
		}

		anthemum::Engine::Instance().Shutdown();


}