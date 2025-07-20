#pragma once

// #include <array>
// #include <functional>
#include "glm/glm.hpp"
#include "glm/gtc/type_precision.hpp"

// class Chunk;
// class Cell;

// void SandStep(Chunk* c, Cell cell);

struct Cell
{
	glm::uint8 id = 0;
	glm::i8vec2 position = { 0, 0 };
	glm::i8vec2 velocity = { 0, 0 };
	glm::u8vec4 color = { 0, 0, 0, 0 };

	// void Step(Chunk* c)
	// {
	// 	SandStep(c, *this);
	// }
	//
	// bool MoveDown(Chunk* c);
};
