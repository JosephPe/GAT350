#pragma once
#include "Vector2.h"
#include "Matrix3_3.h"
#include "MathUtils.h"
#include "Serialization/Serializable.h"

namespace anthemum
{
	struct Transform : public ISerializable
	{
		Vector2 position;
		float rotation{ 0 };
		Vector2 scale{ 1, 1 };
		
		Matrix3_3 matrix;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Update()
		{
			Matrix3_3 mxScale = Matrix3_3::CreateScale(scale);
			Matrix3_3 mxRotation = Matrix3_3::CreateRotation(math::DegToRad(rotation));
			Matrix3_3 mxTranslation = Matrix3_3::CreateTranslation(position);

			matrix = { mxTranslation * mxRotation * mxScale };
		}	
		void Update(const Matrix3_3 parent)
		{
			Matrix3_3 mxScale = Matrix3_3::CreateScale(scale);
			Matrix3_3 mxRotation = Matrix3_3::CreateRotation(math::DegToRad(rotation));
			Matrix3_3 mxTranslation = Matrix3_3::CreateTranslation(position);

			matrix = { mxTranslation * mxRotation * mxScale };
			matrix = parent * matrix;
		}
		
		operator Matrix3_3() const
		{
			Matrix3_3 mxScale = Matrix3_3::CreateScale(scale);
			Matrix3_3 mxRotation = Matrix3_3::CreateRotation(math::DegToRad(rotation));
			Matrix3_3 mxTranslation = Matrix3_3::CreateTranslation(position);
			return { mxTranslation * mxRotation * mxScale };
		}
		

		// Inherited via ISerializable

	};
}