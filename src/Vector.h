#pragma once

#include <string>

namespace math {
	struct Vec2
	{
		Vec2();
		Vec2(float x, float y);

		float x, y;

		Vec2 Normalize();
		double Length();

		std::string ToString();

		// operator has return, left hand operand and right hand operand
		// member functions has left hand operand implicit as this pointer
		Vec2 operator!();
		void operator+(const Vec2& v2);
		void operator-(const Vec2& v2);
		void operator*(float scalar);
	};

	struct Vec3
	{
		Vec3();

		float x, y, z;

	};

	//double Distance();

	// symmetric operators are usually outside the class
	//Vec3 operator+(Vec3& self, Vec3& other);
}
