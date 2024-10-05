#pragma once

#include "Element.h"

class Water : public Liquid
{
public:
	Water(glm::vec2 pos = glm::vec2(0, 0)) : Liquid()
	{
		ID = 4;
		Position = pos;
		Velocity = { 0, 0 };
		Color = glm::vec4(0.2f, 0.5f, 0.8f, 0.6f);
	}

	void Step(World* world) override
	{
		glm::ivec2 pos = Position;

		Element* element = world->GetElementAtWorldPos(pos);
		Element* elementB = world->GetElementAtWorldPos(pos + glm::ivec2(0, -1));
		Element* elementBR = world->GetElementAtWorldPos(pos + glm::ivec2(1, 0));
		Element* elementBL = world->GetElementAtWorldPos(pos + glm::ivec2(-1, 0));

		if (elementB != nullptr && elementB->ID == 0)
		{
			world->SetElementAtWorldPos(pos, elementB);
			world->SetElementAtWorldPos(pos + glm::ivec2(0, -1), element);
		}
		else if (elementBR != nullptr && elementBR->ID == 0)
		{
			world->SetElementAtWorldPos(pos, elementBR);
			world->SetElementAtWorldPos(pos + glm::ivec2(1, 0), element);
		}
		else if (elementBL != nullptr && elementBL->ID == 0)
		{
			world->SetElementAtWorldPos(pos, elementBL);
			world->SetElementAtWorldPos(pos + glm::ivec2(-1, 0), element);
		}
	}

private:

};