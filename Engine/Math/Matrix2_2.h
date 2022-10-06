#pragma once
#include <Engine.h>

namespace anthemum
{
	struct Matrix2_2
	{
		Vector2 rows[2]; // [2] [2]

		Matrix2_2() = default;
		Matrix2_2(const Vector2& row1, const Vector2& row2);

		Vector2 operator [] (size_t index) const { return rows[index]; }
		Vector2& operator [] (size_t index) { return rows[index]; }

		Vector2 operator * (const Vector2& v); // mx22 * v2

		Matrix2_2 operator * (const Matrix2_2& mx); // mx22 = mx22 * mx22

		static Matrix2_2 CreateScale(const Vector2& scale);
		static Matrix2_2 CreateScale(float scale);
		static Matrix2_2 CreateRotation(float radians);

		static const Matrix2_2 identity;
		static const Matrix2_2 zero;

	};


	inline Matrix2_2::Matrix2_2(const Vector2& row1, const Vector2& row2)
	{
		rows[0] = row1;
		rows[1] = row2;
	}

	inline Vector2 Matrix2_2::operator*(const Vector2& v)
	{
		Vector2 result;

		result.x = v.x * rows[0][0] + v.y * rows[0][1];
		result.y = v.x * rows[1][0] + v.y * rows[1][1];

		return result;
	}

	inline Matrix2_2 Matrix2_2::operator*(const Matrix2_2& mx)
	{
		Matrix2_2 result;

		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0];
		result[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0];
		result[0][1] = rows[0][1] * mx[0][0] + rows[1][1] * mx[0][1];
		result[1][1] = rows[1][1] * mx[0][0] + rows[1][1] * mx[1][1];
	}
	
	inline Matrix2_2 Matrix2_2::CreateScale(const Vector2& scale)
	{
		Matrix2_2 mx;

		//nonuniform
		// sx 0
		// 0 sY

		mx[0] = Vector2{ scale.x, 0.0f };
		mx[1] = Vector2{ 0.0f, scale.y };

		return mx;
	}
	inline Matrix2_2 Matrix2_2::CreateScale(float scale)
	{
		Matrix2_2 mx;

		//uniform
		// sx 0
		// 0 sY

		mx[0] = Vector2{ scale, 0.0f };
		mx[1] = Vector2{ 0.0f, scale };

		return mx;
	}
	inline Matrix2_2 Matrix2_2::CreateRotation(float radians)
	{
		Matrix2_2 mx;

		float c = std::cos(radians);
		float s = std::sin(radians);

		mx[0] = Vector2{ c, -s };
		mx[1] = Vector2{ s, c};

		return mx;
	}
};