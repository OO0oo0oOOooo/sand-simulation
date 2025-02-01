#pragma once

#include "Cell.h"

class Air : public Gas
{
public:
	Air(int px, int py)
	{
		Id = 0;

		Position = { px, py };
		Color = { 0, 0, 0, 0 };
	}

	~Air() {}
};