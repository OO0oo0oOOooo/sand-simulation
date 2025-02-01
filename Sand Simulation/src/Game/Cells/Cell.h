#pragma once

// TODO: make cell a class

#include <array>
#include <functional>

#include "glm/glm.hpp"
#include "glm/gtc/type_precision.hpp"

class Chunk;
class Cell;

void SandStep(Chunk* c, Cell cell);

struct Cell
{
	glm::uint8 id = 0;
	glm::i8vec2 position = { 0, 0 };
	glm::i8vec2 velocity = { 0, 0 };
	glm::u8vec4 color = { 0, 0, 0, 0 };

	void Step(Chunk* c)
	{
		SandStep(c, *this);
	}

	bool MoveDown(Chunk* c);
};

//class Cell
//{
//public:
//	void Step() { return; }
//	void ActOnOther() { return; }
//
//public:
//	std::uint8_t id = 0;
//	glm::i8vec2 position = { 0, 0 };
//	glm::i8vec2 velocity = { 0, 0 };
//	glm::u8vec4 color = { 0, 0, 0, 0 };
//};

/*
class Cell
{
public:
	virtual void Step() { return; }

	virtual bool ActOnOther()
	{
		return false;
	}

	virtual bool ReceiveHeat()
	{
		return false;
	}

	virtual bool DarkenColor()
	{
		return false;
	}

public:
	std::uint8_t Id = 0;
	glm::i8vec2 Position = { 0, 0 };
	glm::i8vec2 Velocity = { 0, 0 };
	glm::u8vec4 Color = { 0, 0, 0, 0 };
};



class Liquid : public Cell
{
public:
	Liquid() {}
	~Liquid() {}

private:

};



class Solid : public Cell
{
public:
	Solid() {}
	~Solid() {}

private:

};



class Gas : public Cell
{
public:
	Gas() {}
	~Gas() {}

private:

};



class Particle
{
public:
	Particle() {}
	~Particle() {}

private:

};
*/