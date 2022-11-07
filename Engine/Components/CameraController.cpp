#include "CameraController.h" 
#include "Engine.h" 

namespace anthemum
{
	void CameraController::Update()
	{
		// update transform 

		if (g_inputSystem.GetKeyState(key_a) == InputSystem::keyState::held)
			m_owner->m_transform.position.x -= speed * g_time.deltaTime;

		if (g_inputSystem.GetKeyState(key_d) == InputSystem::keyState::held)
			m_owner->m_transform.position.x += speed * g_time.deltaTime;
		if (g_inputSystem.GetKeyState(key_w) == InputSystem::keyState::held)
			m_owner->m_transform.position.y += speed * g_time.deltaTime;

		if (g_inputSystem.GetKeyState(key_s) == InputSystem::keyState::held)
			m_owner->m_transform.position.y -= speed * g_time.deltaTime;
	}

	bool CameraController::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool CameraController::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);

		return true;
	}

}