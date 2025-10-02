#include <Windows.h>
#include <iostream>
#include <print>
#include <GLFW/glfw3.h>

#include "Vector.h"

void VectorTests()
{
	std::println("Testing vector structs");

	math::Vec2 v1 = { 2.f, 10.f };
	//math::Vec2 v1 = { 3.f, 4.f };
	math::Vec2 v2 = { 10.f, 2.f };
	math::Vec2 v3;

	v3 = v1 + v2;
	std::println("Vector 1: {0}; Vector 2: {1}; Vector 1 + Vector 2: {2}", v1.ToString(), v2.ToString(), v3.ToString());

	v3 = v1 - v2;
	std::println("Vector 1: {0}; Vector 2: {1}; Vector 1 - Vector 2: {2}", v1.ToString(), v2.ToString(), v3.ToString());

	v3 = v1 * 2;
	std::println("Vector 1: {0}; Vector 1 * 2: {1}", v1.ToString(), v3.ToString());

	std::println("Vector 1: {0}; Vector 1 length: {1}", v1.ToString(), v1.Length());

	v3 = v1.Normalize();
	std::println("Vector 1: {0}; Vector 1 normalized: {1}", v1.ToString(), v3.ToString());
}

int main()
{
	std::println("Game Maths with OpenGL and C++ 23!!\n");

	//VectorTests();

	

	std::cin.get();

	return 0;
}