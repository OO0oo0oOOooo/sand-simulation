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

	//void Step(World* world) override
	//{
	//	// world->MoveElement(pos)
	//	// world->SwapElements(pos1, pos2)

	//	glm::ivec2 pos = Position;
	//
	//	Element* elementB = world->GetElementAtWorldPos(pos + glm::ivec2(0, -1));
	//	Element* elementBR = world->GetElementAtWorldPos(pos + glm::ivec2(1, -1));
	//	Element* elementBL = world->GetElementAtWorldPos(pos + glm::ivec2(-1, -1));

	//	if (elementB->ID == 0)
	//	{
	//		world->SetElementAtWorldPos(pos, elementB);
	//		world->SetElementAtWorldPos(pos + glm::ivec2(0, -1), this);
	//	}
	//	else if (elementBR->ID == 0)
	//	{
	//		world->SetElementAtWorldPos(pos, elementBR);
	//		world->SetElementAtWorldPos(pos + glm::ivec2(1, -1), this);
	//	}
	//	else if (elementBL->ID == 0)
	//	{
	//		world->SetElementAtWorldPos(pos, elementBL);
	//		world->SetElementAtWorldPos(pos + glm::ivec2(-1, -1), this);
	//	}
	//}

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