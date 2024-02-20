#pragma once

#include "Element.h"

class Empty : public Solid
{
public:
	Empty()
	{
		ID = 255;
		Position = { 0, 0 };
		Velocity = { 0, 0 };
		Color = { 0, 0, 0, 0 };
	}

	~Empty() {}

private:

};

