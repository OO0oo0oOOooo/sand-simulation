#pragma once

#include <glm/glm.hpp>

class Element
{
public:
	Element() {}
	~Element() {}

	virtual void Step()
	{
		return;
	}

	virtual bool ActOnOther()
	{
		return false;
	}

	virtual bool ReceiveHeat() 
	{
		return false;
	}

	virtual bool  DarkenColor()
	{
		return false;
	}

	int id = 0;

	glm::vec2 position = { 0, 0 };
	glm::vec2 velocity = { 0, 0 };
	glm::vec4 color = { 0, 0, 0, 0 };

private:

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