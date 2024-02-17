#pragma once

#include "Element.h"

class Sand : public Solid
{
public:
	Sand(glm::vec2 pos = glm::vec2(0, 0)) 
	{
		ID = 3;
		Position = pos;
		Velocity = { 0, 0 };
		Color = { 0.9f, 0.7f, 0.2f, 1.0f };
	}

	~Sand() {}

	void Step() override
	{
		//Element elementBL = GetElementAtPosition(position - {-1, -1});
		//Element elementB = GetElementAtPosition(position - {0, -1});
		//Element elementBR = GetElementAtPosition(position - {1, -1});

		

	}

	//bool ActOnOther() override
	//{
	//	return false;
	//}

	//bool ReceiveHeat() override
	//{
	//	return true;
	//}

	//bool DarkenColor() override
	//{
	//	return true;
	//}	

private:

};