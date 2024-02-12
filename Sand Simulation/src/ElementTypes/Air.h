#pragma once

#include "Element.h"

class Air : public Gas
{
public:
	Air() {}
	~Air() {}

	void Step() override
	{
		return;
	}

};