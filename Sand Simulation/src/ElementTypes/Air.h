#pragma once

#include "Element.h"

class Air : public Gas
{
public:
	Air(glm::vec2 pos = glm::vec2(0, 0))
	{
		ID = 0;
		Position = pos;
		Velocity = { 0, 0 };
		Color = { 0, 0, 0, 0 };
	}

	~Air() {}

	/*void Step() override
	{
		return;
	}*/

};