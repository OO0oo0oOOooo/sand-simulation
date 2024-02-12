#pragma once

#include "Element.h"

class Sand : public Solid
{
public:
	Sand() {}
	~Sand() {}

	void Step() override
	{
		//Element elementBL = GetElementAtPosition(position - {-1, -1});
		//Element elementB = GetElementAtPosition(position - {0, -1});
		//Element elementBR = GetElementAtPosition(position - {1, -1});

		

	}

	bool ActOnOther() override
	{
		return false;
	}

	bool ReceiveHeat() override
	{
		return true;
	}

	bool DarkenColor() override
	{
		return true;
	}	

private:

};