#include "PlayerComponent.h"
#include <Engine.h>
#include <iostream>
#include <functional>

namespace anthemum
{
	void PlayerComponent::Initialize()
	{
		CharacterComponent::Initialize();
	}

	void PlayerComponent::Update()
	{
		//auto camera = m_owner->GetScene()->GetActorFromName("Camera");
		//if (camera)
		//{
		//camera->m_transform.position = m_owner->m_transform.position;
		//}

		auto camera = m_owner->GetScene()->GetActorFromName("Camera");
		if (camera)
		{
			camera->m_transform.position = math::Lerp(camera->m_transform.position, m_owner->m_transform.position, 2 * g_time.deltaTime);
		}

		Vector2 direction = Vector2::zero;
		if (g_inputSystem.GetKeyState(key_a) == InputSystem::keyState::held)
		{
			direction = Vector2::left;
		}	
		if (g_inputSystem.GetKeyState(key_d) == InputSystem::keyState::held)
		{
			direction = Vector2::right;

		}	

		float thrust = 0;
		if (g_inputSystem.GetKeyState(key_w) == InputSystem::keyState::held)
		{
			thrust = 500;
		}
		//m_owner->m_transform.position += direction * 300 * g_time.deltaTime;
		Vector2 velocity;
		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(direction * speed);
			velocity = component->velocity;
		}

		if (m_groundCount > 0 && g_inputSystem.GetKeyState(key_space) == InputSystem::keyState::Pressed)

			Vector2 velocity;
		//auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			float multiplier = (m_groundCount > 0) ? 1 : 0.2f;

			component->ApplyForce(direction * speed * multiplier);
			velocity = component->velocity;
		}
		
		if (g_inputSystem.GetKeyState(key_space) == InputSystem::keyState::Pressed)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				component->ApplyForce(Vector2::up * 500);
			}
		}

		auto animComponent = m_owner->GetComponent<SpriteAnimComponent>();
		if (animComponent)
		{
			if (velocity.x != 0) animComponent->SetFlipHorizontal(velocity.x < 0);
			if (std::fabs(velocity.x) > 0)
			{
				animComponent->SetSequence("run");
			}
			else
			{
				animComponent->SetSequence("idle");
			}
		}

	}

	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		CharacterComponent::Read(value);

		READ_DATA(value, speed);
		return false;
	}

	void PlayerComponent::OnCollisionEnter(Actor* other)
	{
		if (other->GetTag() == "Ground")
		{
			m_groundCount++;
		}
		if (other->GetName() == "Coin")
		{
			Event event;
			event.name = "EVENT_ADD_POINTS";
			event.data = 100;

			g_eventManager.Notify(event);

			other->SetDestroy();
		}

		if (other->GetTag() == "Enemy")
		{
			Event event;
			event.name = "EVENT_DAMAGE";
			event.data = damage;
			event.receiver = other;

			g_eventManager.Notify(event);
		}
	}

	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		if (other->GetTag() == "Ground")
		{
			m_groundCount--;
		}
	}

	void PlayerComponent::OnNotify(const Event& event)
	{
		if (event.name == "EVENT_DAMAGE")
		{
			health -= std::get<float>(event.data);
			
			if (health <= 0)
			{
				m_owner->SetDestroy();
			}
		}
		
	}

}