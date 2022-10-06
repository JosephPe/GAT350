#pragma once
#include "Framework/Component.h" 
#include "Math/Matrix3_3.h" 

namespace anthemum
{
	class CameraComponent : public Component
	{
	public:
		CLASS_DECLARATION(CameraComponent)

			virtual void Initialize() override;
		virtual void Update() override;

		const Matrix3_3& GetView() { return m_view; }

		void SetViewport(const Vector2& size);
		const Matrix3_3& GetViewport() { return m_viewport; }

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		Vector2 viewport_size;

		Matrix3_3 m_view;
		Matrix3_3 m_viewport;
	};
}
