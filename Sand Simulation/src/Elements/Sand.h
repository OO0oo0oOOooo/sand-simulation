#pragma once

#include "Element.h"
#include "../Chunk.h"

class Sand : public Solid
{
public:
	Sand(int px, int py)
	{
		Id = 3;
		Position = { px, py };
		Color = { 230, 178, 51, 255 };
	}
	
	void Step(Chunk* chunk) override
	{
		//Element element = chunk->GetElement(Position.x, Position.y);
		//Element elementB = chunk->GetElement(Position.x, Position.y - 1);

		//if (elementB.Id == 0)
		//{
		//	chunk->SetElement(Position.x, Position.y, elementB);
		//	chunk->SetElement(Position.x, Position.y - 1, element);
		//}

		//Element element = chunk->GetElement(Position.x, Position.y);
		//Element elementB = chunk->GetElement(Position.x, Position.y - 1);
		//Element elementBR = chunk->GetElement(Position.x + 1, Position.y - 1);
		//Element elementBL = chunk->GetElement(Position.x - 1, Position.y - 1);

		//if (elementB.Id == 0)
		//{
		//	chunk->SetElement(Position.x, Position.y, elementB);
		//	chunk->SetElement(Position.x, Position.y - 1, element);
		//}
		//else if (elementBR.Id == 0)
		//{
		//	chunk->SetElement(Position.x, Position.y, elementBR);
		//	chunk->SetElement(Position.x + 1, Position.y - 1, element);
		//}
		//else if (elementBL.Id == 0)
		//{
		//	chunk->SetElement(Position.x, Position.y, elementBL);
		//	chunk->SetElement(Position.x - 1, Position.y - 1, element);
		//}
	}

	/*
	void Step(Chunk* chunk) 
	{
		Element element = chunk->GetElement(Position.x, Position.y);
		Element elementB = chunk->GetElement(Position.x, Position.y - 1);
		Element elementBR = chunk->GetElement(Position.x + 1, Position.y - 1);
		Element elementBL = chunk->GetElement(Position.x - 1, Position.y - 1);

		if (elementB.Id == 0)
		{
			chunk->SetElement(Position.x, Position.y, elementB);
			chunk->SetElement(Position.x, Position.y - 1, element);
		}
		else if (elementBR.Id == 0)
		{
			chunk->SetElement(Position.x, Position.y, elementBR);
			chunk->SetElement(Position.x + 1, Position.y - 1, element);
		}
		else if (elementBL.Id == 0)
		{
			chunk->SetElement(Position.x, Position.y, elementBL);
			chunk->SetElement(Position.x - 1, Position.y - 1, element);
		}
	}
	*/

	/*
	std::array<int, 9> Step(std::array<int, 9> neighbours)
	{
		std::array<int, 9> newNeighbours = neighbours;

		const int& TL = neighbours[0];
		const int& T = neighbours[1];
		const int& TR = neighbours[2];
		const int& ML = neighbours[3];
		const int& M = neighbours[4];
		const int& MR = neighbours[5];
		const int& BL = neighbours[6];
		const int& B = neighbours[7];
		const int& BR = neighbours[8];

		if (!B)
		{
			newNeighbours[4] = 0;
			newNeighbours[7] = 1;
		}
		else if (!BR)
		{
			newNeighbours[4] = 0;
			newNeighbours[8] = 1;
		}
		else if (!BL)
		{
			newNeighbours[4] = 0;
			newNeighbours[6] = 1;

		}

		return newNeighbours;
	}*/

	/*std::array<int, 9> Step(std::array<int, 9> neighbours)
	{
		std::array<int, 9> newNeighbours = neighbours;

		const int &TL = neighbours[0];
		const int &T = neighbours[1];
		const int &TR = neighbours[2];
		const int &ML = neighbours[3];
		const int &M = neighbours[4];
		const int &MR = neighbours[5];
		const int &BL = neighbours[6];
		const int &B = neighbours[7];
		const int &BR = neighbours[8];

		if (!B)
		{
			newNeighbours[4] = 0;
			newNeighbours[7] = 1;
		}
		else if (!BR)
		{
			newNeighbours[4] = 0;
			newNeighbours[8] = 1;
		}
		else if (!BL)
		{
			newNeighbours[4] = 0;
			newNeighbours[6] = 1;

		}

		return newNeighbours;
	}*/
};













/*
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

	void Step(World* world)
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

				if (rand() % 2)
				{
					Element* elementBR = world->GetElementAtWorldPos(lastStep + glm::ivec2(1, -1));
					if (elementBR != nullptr && elementBR->ID == 0)
					{
						world->SetElementAtWorldPos(lastStep, elementBR);
						world->SetElementAtWorldPos(lastStep + glm::ivec2(1, -1), this);
					}
				}
				else
				{
					Element* elementBL = world->GetElementAtWorldPos(lastStep + glm::ivec2(-1, -1));
					if (elementBL != nullptr && elementBL->ID == 0)
					{
						world->SetElementAtWorldPos(lastStep, elementBL);
						world->SetElementAtWorldPos(lastStep + glm::ivec2(-1, -1), this);
					}
				}
				break;
			}

			
			
			//Element* stepEle = world->GetElementAtWorldPos(step);
			//if (stepEle == nullptr) return;
			//if (stepEle->ID == 0)
			//{
			//	Velocity = vel;
			//	world->SetElementAtWorldPos(lastStep, stepEle);
			//	world->SetElementAtWorldPos(step, this);
			//	lastStep = step;
			//}
			//else
			//{
			//	Velocity = { 0, 0 };
			//	Element* elementB = world->GetElementAtWorldPos(step + glm::ivec2(0, -1));
			//	Element* elementBR = world->GetElementAtWorldPos(step + glm::ivec2(1, -1));
			//	Element* elementBL = world->GetElementAtWorldPos(step + glm::ivec2(-1, -1));
			//	if (elementB != nullptr && elementB->ID == 0)
			//	{
			//		world->SetElementAtWorldPos(step, elementB);
			//		world->SetElementAtWorldPos(step + glm::ivec2(0, -1), stepEle);
			//	}
			//	else if (elementBR != nullptr && elementBR->ID == 0)
			//	{
			//		world->SetElementAtWorldPos(step, elementBR);
			//		world->SetElementAtWorldPos(step + glm::ivec2(1, -1), stepEle);
			//	}
			//	else if (elementBL != nullptr && elementBL->ID == 0)
			//	{
			//		world->SetElementAtWorldPos(step, elementBL);
			//		world->SetElementAtWorldPos(step + glm::ivec2(-1, -1), stepEle);
			//	}
			//	break;
			//}
		}
	}

	void StepConditions(World* world, glm::ivec2 pos)
	{
		Element* element = world->GetElementAtWorldPos(pos);
		Element* elementB = world->GetElementAtWorldPos(pos + glm::ivec2(0, -1));
		Element* elementBR = world->GetElementAtWorldPos(pos + glm::ivec2(1, -1));
		Element* elementBL = world->GetElementAtWorldPos(pos + glm::ivec2(-1, -1));

		if (elementB != nullptr && elementB->ID == 0)
		{
			world->SetElementAtWorldPos(pos, elementB);
			world->SetElementAtWorldPos(pos + glm::ivec2(0, -1), element);
		}
		else if (elementBR != nullptr && elementBR->ID == 0)
		{
			world->SetElementAtWorldPos(pos, elementBR);
			world->SetElementAtWorldPos(pos + glm::ivec2(1, -1), element);
		}
		else if (elementBL != nullptr && elementBL->ID == 0)
		{
			world->SetElementAtWorldPos(pos, elementBL);
			world->SetElementAtWorldPos(pos + glm::ivec2(-1, -1), element);
		}
	}
};
*/