#pragma once

#include <glm/glm.hpp>



//namespace Elements {
//
//	Empty empty;
//	Air air;
//	Sand sand;
//
//}

#include "Air.h"
#include "Sand.h"
#include "Water.h"
#include "Empty.h"

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

	int ID = 0;
	glm::vec2 Position = { 0, 0 };
	glm::vec2 Velocity = { 0, 0 };
	glm::vec4 Color = { 0, 0, 0, 0 };

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