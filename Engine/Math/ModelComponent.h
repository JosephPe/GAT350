#pragma once
#include "Components/RenderComponent.h"

namespace anthemum
{
	class ModelComponent : public RenderComponent
	{
	public:
		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		CLASS_DECLARATION(ModelComponent)

	public:
		std::shared_ptr<Model> m_model;

		// Inherited via ISerializable
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	};
}