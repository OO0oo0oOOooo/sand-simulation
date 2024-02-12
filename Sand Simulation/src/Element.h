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

private:
	
	int id;

	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec4 color;


};



class Liquid : public Element
{
public:
	Liquid() {}

	~Liquid() {}
	
	bool  DarkenColor() override
	{
		return false;
	}

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

	bool DarkenColor() override
	{
		return false;
	}

private:

};



class Particle
{
public:
	Particle() {}
	~Particle() {}

private:

};