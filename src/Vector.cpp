#include "Vector.h"

#include <print>
#include <cmath>

namespace math {
	/*
		2D Vector struct
	*/

	Vec2::Vec2()
		: x(0.f), y(0.f)
	{
	}

	Vec2::Vec2(float x, float y)
		: x(x), y(y)
	{
	}

	Vec2 Vec2::Normalize()
	{
		if (x != 0 || y != 0)
		{
			Vec2 normal = *this;

			return normal * (1 / Length());
		}

		std::println("ERROR: can't normalize zero vector");

		return Vec2();
	}

	double Vec2::Length()
	{
		return std::sqrt(x * x + y * y);
	}

	std::string Vec2::ToString()
	{
		std::string out;

		out = "[" + std::to_string(x) + " " + std::to_string(y) + "]";

		return out;
	}

	Vec2 Vec2::operator!()
	{
		Vec2 negatedVector;

		negatedVector.x = x * -1;
		negatedVector.y = y * -1;

		return negatedVector;
	}

	/*
		3D Vector struct
	*/

	Vec3::Vec3()
		: x(0.f), y(0.f), z(0.f)
	{
	}

	Vec3::Vec3(float x, float y, float z)
		: x(x), y(y), z(z)
	{
	}

	Vec3 Vec3::Normalize()
	{
		if (x != 0 || y != 0 || z != 0)
		{
			Vec3 normal = *this;

			return normal * (1 / Length());
		}

		std::println("ERROR: can't normalize zero vector");

		return Vec3();
	}

	double Vec3::Length()
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	std::string Vec3::ToString()
	{
		std::string out;

		out = "[" + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + "]";

		return out;
	}

	Vec3 Vec3::operator!()
	{
		Vec3 negatedVector;

		negatedVector.x = x * -1;
		negatedVector.y = y * -1;
		negatedVector.z = z * -1;

		return negatedVector;
	}


	float DotProduct(const Vec2& v1, const Vec2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	float DotProduct(const Vec3& v1, const Vec3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	Vec3 CrossProduct(const Vec3& v1, const Vec3& v2)
	{
		return Vec3();
	}

	double Distance2D(const Vec2& start, const Vec2& end)
	{
		return 0.f;
	}

	double Distance3D(const Vec3& start, const Vec3& end)
	{
		return 0.f;
	}

	Vec2 operator+(const Vec2& v1, const Vec2& v2)
	{
		Vec2 newVec;

		newVec.x = v1.x + v2.x;
		newVec.y = v1.y + v2.y;

		return newVec;
	}

	Vec3 operator+(const Vec3& v1, const Vec3& v2)
	{
		Vec3 newVec;

		newVec.x = v1.x + v2.x;
		newVec.y = v1.y + v2.y;
		newVec.z = v1.z + v2.z;

		return newVec;
	}

	Vec2 operator-(const Vec2& v1, const Vec2& v2)
	{
		Vec2 newVec;

		newVec.x = v1.x - v2.x;
		newVec.y = v1.y - v2.y;

		return newVec;
	}

	Vec3 operator-(const Vec3& v1, const Vec3& v2)
	{
		Vec3 newVec;

		newVec.x = v1.x - v2.x;
		newVec.y = v1.y - v2.y;
		newVec.z = v1.z - v2.z;

		return newVec;
	}

	Vec2 operator*(const Vec2& v, float scalar)
	{
		Vec2 newVec;

		newVec.x = v.x * scalar;
		newVec.y = v.y * scalar;

		return newVec;
	}

	Vec3 operator*(const Vec3& v, float scalar)
	{
		Vec3 newVec;

		newVec.x = v.x * scalar;
		newVec.y = v.y * scalar;
		newVec.z = v.z * scalar;

		return newVec;
	}
}