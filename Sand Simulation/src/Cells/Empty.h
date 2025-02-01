#pragma once

#include "Cell.h"

class Empty : public Solid
{
public:
	Empty()
	{
		Id = 255;
	}

	~Empty() {}

private:

};

