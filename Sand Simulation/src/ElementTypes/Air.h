#pragma once

#include "Element.h"

class Air : public Gas
{
public:
	Air() 
	{
		ID = 0;
		Position = { 0, 0 };
		Velocity = { 0, 0 };
		Color = { 0, 0, 0, 0 };
	}

	~Air() {}

	/*void Step() override
	{
		return;
	}*/

};