#include "InputSystem.h"
#include <SDL.h>
#include <iostream>

using namespace std;

namespace anthemum 
{

	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_w = SDL_SCANCODE_W;
	const uint32_t key_s = SDL_SCANCODE_S;
	const uint32_t key_a = SDL_SCANCODE_A;
	const uint32_t key_d = SDL_SCANCODE_D;
	const uint32_t key_escape = SDL_SCANCODE_ESCAPE;

	const uint32_t button_left = 0;
	const uint32_t button_middle = 1;
	const uint32_t button_right = 2;


	void InputSystem::Initialize()
	{
		const uint8_t* keyboardState = SDL_GetKeyboardState(&m_numKeys);

		m_keyboardState.resize(m_numKeys);
		copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		m_prevKeyboardState = m_keyboardState;
	}

	void InputSystem::Shutdown()
	{
	}

	void InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		m_prevKeyboardState = m_keyboardState;

		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		//cout << (bool)m_keyboardState[SDL_SCANCODE_SPACE];

		m_prevMouseButtonState = m_mouseButtonState;
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = anthemum::Vector2{ x, y };
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [ORML]
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [ORML]
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [ORML]

		//for (auto state : m_keyboardState)
		//{
		//	std::cout << state;
		//}
		//std::cout << std::endl;
	}


	anthemum::InputSystem::keyState InputSystem::GetButtonState(uint32_t button)
	{
		keyState keystate = keyState::Idle;

		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPreviousButtonDown(button);

		if ((buttonDown == true) && (prevButtonDown == false)) 
		{
			keystate = keyState::Pressed;
		}
		if ((buttonDown == true) && (prevButtonDown == true)) 
		{
			keystate = keyState::held;
		}
		if ((buttonDown == false) && (prevButtonDown == true)) {
			keystate = keyState::Released;
		}

		return keystate;
	}

	anthemum::InputSystem::keyState InputSystem::GetKeyState(uint32_t key)
	{
		keyState keystate = keyState::Idle;
		bool keyDown = GetKeyDown(key);
		bool prevKeyDown = GetPreviousKeyDown(key);

		if ((keyDown == true) && (prevKeyDown == false))
		{
			keystate = keyState::Pressed;
		}
		if ((keyDown == true) && (prevKeyDown == true))
		{
			keystate = keyState::held;
		}
		if ((keyDown == false) && (prevKeyDown == true)) {
			keystate = keyState::Released;
		}

		return keystate;
	}

}