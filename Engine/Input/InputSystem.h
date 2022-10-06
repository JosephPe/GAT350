#pragma once
#include <cstdint>
#include <vector>
#include <map>
#include <array>
#include <string>
#include "../Math/Vector2.h"


namespace anthemum
{
	class InputSystem
	{
	public:
		enum class keyState 
		{
		Idle,
		Pressed,
		held,
		Released
		};
	public:
		InputSystem() = default;
		~InputSystem() = default;

		void Initialize();
		void Shutdown();

		void Update();

		bool GetKeyDown(int key) { return m_keyboardState[key]; }
		keyState GetButtonState(uint32_t button);
		keyState GetKeyState(uint32_t key);
		bool GetPreviousKeyDown(uint32_t key) { return m_prevKeyboardState[key]; }

		const Vector2& GetMousePosition() const { return m_mousePosition; }
		bool GetButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
		bool GetPreviousButtonDown(uint32_t button) { return m_prevMouseButtonState[button]; }

	private:
		int m_numKeys;
		
		std::vector<uint8_t> m_keyboardState;
		std::vector<uint8_t> m_prevKeyboardState;


		Vector2 m_mousePosition;
		
		std::array<uint8_t, 3> m_mouseButtonState;
		std::array<uint8_t, 3> m_prevMouseButtonState;
	};

	
	extern const uint32_t key_space;
	extern const uint32_t key_w;
	extern const uint32_t key_s;
	extern const uint32_t key_a;
	extern const uint32_t key_d;
	extern const uint32_t key_escape;

	extern const uint32_t button_left;
	extern const uint32_t button_middle;
	extern const uint32_t button_right;
}