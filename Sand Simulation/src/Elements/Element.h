#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_precision.hpp"

class Chunk;

class Element
{
public:
	virtual void Step(Chunk* chunk) { return; }

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



class Liquid : public Element
{
public:
	Liquid() {}
	~Liquid() {}

private:

};



class Solid : public Element
{
public:
	Solid() {}
	~Solid() {}

private:

};



class Gas : public Element
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