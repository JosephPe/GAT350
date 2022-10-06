#pragma once
#include "GameObject.h"
#include "Renderer/Model.h"
#include "Core/Memory.h"
#include <vector>

namespace anthemum
{
	class Actor;

	class Component : public GameObject, public ISerializable
	{
	public:
		Component() = default;
		~Component() = default;

		virtual void Initialize() override {}
		virtual void Update() = 0;

		friend class Actor;
	protected:
		Actor* m_owner = nullptr;

	};
}