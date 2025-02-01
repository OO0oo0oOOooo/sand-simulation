#pragma once

/*


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
		glm::vec2 vel = Velocity;
		vel.y += -9.81f * Time::deltaTime;

		glm::vec2 currentPosition = Position;
		glm::vec2 targetPosition = currentPosition + vel;

		glm::ivec2 lastStep = currentPosition;

		int cX = currentPosition.x;
		int cY = currentPosition.y;

		int tX = targetPosition.x;
		int tY = targetPosition.y;

		int xDiff = tX - cX;
		int yDiff = tY - cY;

		bool xDiffIsLarger = glm::abs(xDiff) > glm::abs(yDiff);

		int xMod = xDiff > 0 ? 1 : -1;
		int yMod = yDiff > 0 ? 1 : -1;

		int longerSideLength = std::max(glm::abs(xDiff), glm::abs(yDiff));
		int shorterSideLength = std::min(glm::abs(xDiff), glm::abs(yDiff));

		float slope = (shorterSideLength == 0 || longerSideLength == 0) ? 0 : ((float)(shorterSideLength) / (longerSideLength));

		int shorterSideIncrease;

		for (int i = 1; i <= longerSideLength; i++)
		{
			shorterSideIncrease = glm::round(i * slope);
			int yIncrease, xIncrease;
			if (xDiffIsLarger)
			{
				xIncrease = i;
				yIncrease = shorterSideIncrease;
			}
			else
			{
				yIncrease = i;
				xIncrease = shorterSideIncrease;
			}

			int stepY = cY + (yIncrease * yMod);
			int stepX = cX + (xIncrease * xMod);

			glm::ivec2 step = { stepX, stepY };

			Element* stepEle = world->GetElementAtWorldPos(step);

			if (stepEle != nullptr && stepEle->ID == 0)
			{
				Velocity = vel;
				world->SetElementAtWorldPos(lastStep, stepEle);
				world->SetElementAtWorldPos(step, this);
				lastStep = step;
			}
			else
			{
				Velocity = { 0, 0 };
				
				Element* elementBR = world->GetElementAtWorldPos(lastStep + glm::ivec2(1, 0));
				Element* elementBL = world->GetElementAtWorldPos(lastStep + glm::ivec2(-1, 0));

				//if (elementBR != nullptr && elementBL != nullptr && elementBR->ID == 0 && elementBL->ID == 0)
				//{
				//	Velocity = { ((rand() % 7) - 3) * 10 * Time::deltaTime, ((rand() % 7) - 3) * 10 * Time::deltaTime };
				//}

				//if (elementBR != nullptr && elementBR->ID != 0)
				//{
				//	Velocity = { ((rand() % 3)) * 100 * Time::deltaTime, 0 };
				//}

				//if (elementBL != nullptr && elementBL->ID != 0)
				//{
				//	Velocity = { -((rand() % 3)) * 100 * Time::deltaTime, 0 };
				//}
				//
				
				
				if (rand() % 2)
				{
					Element* elementBR = world->GetElementAtWorldPos(lastStep + glm::ivec2(1, 0));
					if (elementBR != nullptr && elementBR->ID == 0)
					{
						world->SetElementAtWorldPos(lastStep, elementBR);
						world->SetElementAtWorldPos(lastStep + glm::ivec2(1, 0), this);
					}
				}
				else
				{
					Element* elementBL = world->GetElementAtWorldPos(lastStep + glm::ivec2(-1, 0));
					if (elementBL != nullptr && elementBL->ID == 0)
					{
						world->SetElementAtWorldPos(lastStep, elementBL);
						world->SetElementAtWorldPos(lastStep + glm::ivec2(-1, 0), this);
					}
				}

				break;
			}
		}
	}

	//void Step(World* world) override
	//{
	//	glm::ivec2 pos = Position;

	//	Element* element = world->GetElementAtWorldPos(pos);
	//	Element* elementB = world->GetElementAtWorldPos(pos + glm::ivec2(0, -1));
	//	Element* elementBR = world->GetElementAtWorldPos(pos + glm::ivec2(1, 0));
	//	Element* elementBL = world->GetElementAtWorldPos(pos + glm::ivec2(-1, 0));

	//	if (elementB != nullptr && elementB->ID == 0)
	//	{
	//		world->SetElementAtWorldPos(pos, elementB);
	//		world->SetElementAtWorldPos(pos + glm::ivec2(0, -1), element);
	//	}
	//	else if (elementBR != nullptr && elementBR->ID == 0)
	//	{
	//		world->SetElementAtWorldPos(pos, elementBR);
	//		world->SetElementAtWorldPos(pos + glm::ivec2(1, 0), element);
	//	}
	//	else if (elementBL != nullptr && elementBL->ID == 0)
	//	{
	//		world->SetElementAtWorldPos(pos, elementBL);
	//		world->SetElementAtWorldPos(pos + glm::ivec2(-1, 0), element);
	//	}
	//}

private:

};

*/