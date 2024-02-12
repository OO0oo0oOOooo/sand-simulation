#pragma once

#include "Element.h"

class Water : public Liquid
{
public:
	Water() {}
	~Water() {}

	void Step() override
	{
		//Element elementBL = GetElementAtPosition(position - {-1, 0});
		//Element elementB = GetElementAtPosition(position - {0, -1});
		//Element elementBR = GetElementAtPosition(position - {1, 0});
	}

private:

};