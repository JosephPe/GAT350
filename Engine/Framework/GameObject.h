#pragma once
#include "Serialization/Serializable.h"

#define CLASS_DECLARATION(class)\
	std::unique_ptr<GameObject> Clone() { return std::make_unique<class>(*this); }

#define REGISTER_CLASS(class) anthemum::Factory::Instance().Register<class>(#class);

namespace anthemum 
{
	class GameObject
	{
	public:
		GameObject() = default;

		virtual std::unique_ptr<GameObject> Clone() = 0;
		virtual void Initialize() = 0;
		virtual void Update() = 0;
	};
}
