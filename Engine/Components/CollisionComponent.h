#pragma once
#include "Framework/Component.h"
#include "Physics/Collision.h"
#include "Physics/PhysicsSystem.h"
#include <functional>

namespace anthemum
{
	class CollisionComponent : public Component, public ICollision
	{
	public:

		using functionPTR = std::function<void(Actor*)>;
	public:

		// Inherited via Component
		virtual void Initialize() override;
		virtual void Update() override;

		CLASS_DECLARATION(CollisionComponent)

		// Inherited via ICollision
		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;

		void SetCollisionEnter(functionPTR function) { m_enterFunction = function; }
		void SetCollisionExit(functionPTR function) { m_exitFunction = function; }

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	private:
		PhysicsSystem::CollisionData data;
		Vector2 scale_offset = Vector2{ 1, 1 };

		functionPTR m_enterFunction;
		functionPTR m_exitFunction;
	};
}