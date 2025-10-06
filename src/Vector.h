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
		
	};

	struct Vec3
	{
		Vec3();
		Vec3(float x, float y, float z);

		float x, y, z;

		Vec3 Normalize();
		double Length();

		std::string ToString();

		Vec3 operator!();
	};

	/*
		Vector math functions
	*/
	float DotProduct(const Vec2& v1, const Vec2& v2);
	float DotProduct(const Vec3& v1, const Vec3& v2);

	Vec3 CrossProduct(const Vec3& v1, const Vec3& v2);

	/* 
		Utils Functions
	*/

	double Distance2D(const Vec2& start, const Vec2& end);
	double Distance3D(const Vec3& start, const Vec3& end);

	// symmetric operators are usually outside the class
	
	/////////////////////////
	/* 2D Vector operators */
	////////////////////////

	Vec2 operator+(const Vec2& v1, const Vec2& v2);
	Vec2 operator-(const Vec2& v1, const Vec2& v2);
	Vec2 operator*(const Vec2& v, float scalar);

	/////////////////////////
	/* 3D Vector operators */
	////////////////////////

	Vec3 operator+(const Vec3& v1, const Vec3& v2);
	Vec3 operator-(const Vec3& v1, const Vec3& v2);
	Vec3 operator*(const Vec3& v, float scalar);
}
