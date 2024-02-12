#pragma once

#include "Element.h"

class Steam : public Gas
{
public:
	Steam() {}
	~Steam() {}

	void Step() override
	{
		//Element elementTL = GetElementAtPosition(position - {-1, 1});
		//Element elementT = GetElementAtPosition(position - {0, 1});
		//Element elementTR = GetElementAtPosition(position - {1, 1});
	}

private:

};