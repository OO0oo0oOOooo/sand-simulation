#include "Cell.h"
#include "../Chunk.h"
#include <vector>
#include <functional>

// Solutions
// Array of all positions in between including the end
// Function Pointer 

template<typename... Args>
void LineSolver(glm::ivec2 start, glm::ivec2 end, const std::function<void(Args...)> f)
{
	int cX = start.x;
	int cY = start.y;
	int tX = end.x;
	int tY = end.y;

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
	}
}

std::vector<glm::ivec2> LineSolver(glm::ivec2 start, glm::ivec2 end)
{
	std::vector<glm::ivec2> points;

	int cX = start.x;
	int cY = start.y;
	int tX = end.x;
	int tY = end.y;

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

		points.push_back(step);
	}

	return points;
}

void SandStep(Chunk* chunk, Cell cell)
{
	if (cell.id != 3) return;

	int x = cell.position.x;
	int y = cell.position.y;

	Cell below = chunk->GetCell(x, y - 1);
	Cell left  = chunk->GetCell(x - 1, y);
	Cell right = chunk->GetCell(x + 1, y);
	Cell bleft = chunk->GetCell(x - 1, y - 1);
	Cell bright = chunk->GetCell(x + 1, y - 1);

	if (below.id == 0)
	{
		cell.velocity.y++;
		chunk->SetCell(x, y, below);
		chunk->SetCell(x, y - 1, cell);
		return;
	}
	else if (left.id == 0 && bleft.id == 0)
	{
		cell.velocity.x--;
		chunk->SetCell(x, y, bleft);
		chunk->SetCell(x - 1, y - 1, cell);
		return;
	}
	else if (right.id == 0 && bright.id == 0)
	{
		cell.velocity.x++;
		chunk->SetCell(x, y, bright);
		chunk->SetCell(x + 1, y - 1, cell);
		return;
	}
}

/*
void SandStep(Chunk* chunk, Cell cell)
{
	//if (cell.id != 3) return;

	//int x = cell.position.x;
	//int y = cell.position.y;

	//Cell below = chunk->GetCell(x, y - 1);
	//Cell left  = chunk->GetCell(x - 1, y);
	//Cell right = chunk->GetCell(x + 1, y);
	//Cell bleft = chunk->GetCell(x - 1, y - 1);
	//Cell bright = chunk->GetCell(x + 1, y - 1);

	//if (below.id == 0)
	//{
	//	chunk->SetCell(x, y, below);
	//	chunk->SetCell(x, y - 1, cell);
	//	return;
	//}
	//else if (left.id == 0 && bleft.id == 0)
	//{
	//	chunk->SetCell(x, y, bleft);
	//	chunk->SetCell(x - 1, y - 1, cell);
	//	return;
	//}
	//else if (right.id == 0 && bright.id == 0)
	//{
	//	chunk->SetCell(x, y, bright);
	//	chunk->SetCell(x + 1, y - 1, cell);
	//	return;
	//}

	//if (below.id == 0)
	//{
	//	cell.velocity.y = 1;
	//	chunk->SetCell(x, y, below);
	//	chunk->SetCell(x, y - 1, cell);
	//	return;
	//}
	//
	//if(cell.velocity.x == 0 && cell.velocity.y != 0)
	//{
	//	if (left.id == 0 && right.id == 0)
	//	{
	//		int r = (rand() % 3) - 1;
	//		if(r == -1)
	//			cell.velocity.x = -1;
	//		else if(r == 1)
	//			cell.velocity.x = 1;
	//	}
	//	else if (left.id == 0 && right.id != 0)
	//	{
	//		cell.velocity.x = -1;
	//	}
	//	else if (right.id == 0 && left.id != 0)
	//	{
	//		cell.velocity.x = 1;
	//	}
	//	else
	//	{
	//		cell.velocity.x = 0;
	//	}

	//	cell.velocity.y = 0;
	//}

	//if (cell.velocity.x < 0)
	//{
	//	if (left.id == 0)
	//	{
	//		//cell.velocity.x++;
	//		chunk->SetCell(x, y, left);
	//		chunk->SetCell(x - 1, y, cell);
	//		return;
	//	}
	//	else
	//	{
	//		cell.velocity.x = 0;
	//	}
	//}

	//if (cell.velocity.x > 0)
	//{
	//	if (right.id == 0)
	//	{
	//		//cell.velocity.x--;
	//		chunk->SetCell(x, y, right);
	//		chunk->SetCell(x + 1, y, cell);
	//		return;
	//	}
	//	else
	//	{
	//		cell.velocity.x = 0;
	//	}
	//}

	//chunk->SetCell(x, y, cell);
}
*/

// "Friction" might be better after the move block
// Try more ways to transfer y momentum into x momentum
//void SandStep(Chunk* chunk, Cell cell)
//{
//	if (cell.id != 3) return;
//
//	int x = (int)cell.position.x;
//	int y = (int)cell.position.y;
//
//	if (chunk->GetCell(x, y - 1).id != 0)
//	{
//		if (cell.velocity.x == 0 && cell.velocity.y == 0)
//			return;
//	}
//	else
//	{
//		if (cell.velocity.y < 4 && cell.velocity.y > -4)
//			cell.velocity.y += -1;
//	}
//
//	int targetX = (int)(cell.position.x + cell.velocity.x);
//	int targetY = (int)(cell.position.y + cell.velocity.y);
//
//	if (cell.velocity.x > 0)
//		cell.velocity.x -= 1;
//
//	if (cell.velocity.x < 0)
//		cell.velocity.x += 1;
//
//	std::vector<glm::ivec2> points = LineSolver({ x, y }, { targetX, targetY });
//	glm::ivec2 p = points[0];
//	Cell newCell = chunk->GetCell(p.x, p.y);
//	
//	if (newCell.id == 0)
//	{
//		chunk->SetCell(x, y, newCell);
//		chunk->SetCell(p.x, p.y, cell);
//		return;
//	}
//	else
//	{
//		int ny = std::abs((int)cell.velocity.y);
//		//cell.velocity.x = -cell.velocity.x;
//
//		if (cell.velocity.x == 0)
//		{
//			Cell l = chunk->GetCell(x - 1, y);
//			Cell r = chunk->GetCell(x + 1, y);
//			if (l.id == 0 && r.id == 0)
//			{
//				if (rand() % 2 == 0)
//					cell.velocity.x = -ny;
//				else
//					cell.velocity.x = ny;
//			}
//			else if (l.id == 0 && r.id != 0)
//				cell.velocity.x = -ny;
//			else if (l.id != 0 && r.id == 0)
//				cell.velocity.x = ny;
//		}
//
//		cell.velocity.y = 0;
//		chunk->SetCell(x, y, cell);
//	}
//}

//void SandStep(Chunk* chunk, Cell cell)
//{
//	if (cell.id != 3) { return; }
//	
//	int x = (int)cell.position.x;
//	int y = (int)cell.position.y;
//
//	int targetX = x;
//	int targetY = y - 1;
//	Cell targetCell = chunk->GetCell(targetX, targetY);
//
//	if (targetCell.id == 0)
//	{
//		cell.velocity.y += -1;
//		chunk->SetCell(x, y, targetCell);
//		chunk->SetCell(targetX, targetY, cell);
//		return;
//	}
//	
//	if (cell.velocity.y == 0) // replace with some bool to represent that the cell has momentum
//		return;
//
//
//
//
//	Cell l = chunk->GetCell(x - 1, y);
//	Cell r = chunk->GetCell(x + 1, y);
//	int rx = rand() % 2;
//
//
//
//	if (rx)
//	{
//		if (l.id == 0)
//		{
//			chunk->SetCell(x, y, l);
//			chunk->SetCell(x-1, y, cell);
//		}
//	}
//	else
//	{
//		if (r.id == 0)
//		{
//			chunk->SetCell(x, y, r);
//			chunk->SetCell(x + 1, y, cell);
//		}
//	}
//}

//void SandStep(Chunk* chunk, Cell cell)
//{
//	if (cell.id != 3) return;
//
//	int x = (int)cell.position.x;
//	int y = (int)cell.position.y;
//	Cell belowCell = chunk->GetCell(x, y - 1);
//
//	if (belowCell.id != 0)
//	{
//		cell.velocity.y = 0;
//		return;
//	}
//
//	//if (cell.velocity.y < 4 && cell.velocity.y > -4)
//	//	cell.velocity.y += -1; // Todo: Gravity constant for id
//
//	int targetX = (int)(cell.position.x + cell.velocity.x);
//	int targetY = (int)(cell.position.y + cell.velocity.y);
//	std::vector<glm::ivec2> points = LineSolver({ x, y }, { targetX, targetY });
//
//	//reverse iterate
//	for (int i = points.size()-1; i > 0; i--)
//	{
//		glm::ivec2 p = points[i];
//		Cell newCell = chunk->GetCell(p.x, p.y);
//		if (chunk->GetCell(p.x, p.y).id == 0)
//		{
//			chunk->SetCell(x, y, newCell);
//			chunk->SetCell(p.x, p.y, cell);
//			return;
//		}
//		else
//		{
//			cell.velocity.y = 0;
//			cell.velocity.x = (rand() % 3) - 1;
//		}
//	}
//
//	chunk->SetCell(x, y, cell);
//
//	//if (cell.id == 3 && targetCell.id == 0)
//	//{
//	//	chunk->SetCell(x, y, targetCell);
//	//	chunk->SetCell(targetX, targetY, cell);
//	//}
//}






// TODO: Delete this graveyard


//template<typename... Args>
//void LineSolver(glm::ivec2 start, glm::ivec2 end, const std::function<void(Args...)> f)
//{
//	//glm::ivec2 lastStep = currentPosition;
//	int cX = start.x;
//	int cY = start.y;
//	int tX = end.x;
//	int tY = end.y;
//
//	int xDiff = tX - cX;
//	int yDiff = tY - cY;
//
//	bool xDiffIsLarger = glm::abs(xDiff) > glm::abs(yDiff);
//	int xMod = xDiff > 0 ? 1 : -1;
//	int yMod = yDiff > 0 ? 1 : -1;
//
//	int longerSideLength = std::max(glm::abs(xDiff), glm::abs(yDiff));
//	int shorterSideLength = std::min(glm::abs(xDiff), glm::abs(yDiff));
//
//	float slope = (shorterSideLength == 0 || longerSideLength == 0) ? 0 : ((float)(shorterSideLength) / (longerSideLength));
//	int shorterSideIncrease;
//
//	for (int i = 1; i <= longerSideLength; i++)
//	{
//		shorterSideIncrease = glm::round(i * slope);
//		int yIncrease, xIncrease;
//		if (xDiffIsLarger)
//		{
//			xIncrease = i;
//			yIncrease = shorterSideIncrease;
//		}
//		else
//		{
//			yIncrease = i;
//			xIncrease = shorterSideIncrease;
//		}
//
//		int stepY = cY + (yIncrease * yMod);
//		int stepX = cX + (xIncrease * xMod);
//
//		glm::ivec2 step = { stepX, stepY };
//
//		// Funtion pointer
//
//		//Cell stepCell = chunk->GetCell(step);
//		//if (stepEle != nullptr && stepEle->ID == 0)
//		//{
//		//	Velocity = vel;
//		//	world->SetElementAtWorldPos(lastStep, stepEle);
//		//	world->SetElementAtWorldPos(step, this);
//		//	lastStep = step;
//		//}
//		//else
//		//{
//		//	Velocity = { 0, 0 };
//		//	if (rand() % 2)
//		//	{
//		//		Element* elementBR = world->GetElementAtWorldPos(lastStep + glm::ivec2(1, -1));
//		//		if (elementBR != nullptr && elementBR->ID == 0)
//		//		{
//		//			world->SetElementAtWorldPos(lastStep, elementBR);
//		//			world->SetElementAtWorldPos(lastStep + glm::ivec2(1, -1), this);
//		//		}
//		//	}
//		//	else
//		//	{
//		//		Element* elementBL = world->GetElementAtWorldPos(lastStep + glm::ivec2(-1, -1));
//		//		if (elementBL != nullptr && elementBL->ID == 0)
//		//		{
//		//			world->SetElementAtWorldPos(lastStep, elementBL);
//		//			world->SetElementAtWorldPos(lastStep + glm::ivec2(-1, -1), this);
//		//		}
//		//	}
//		//	break;
//	}
//}


	//glm::vec2 vel = Velocity;
	//vel.y += -9.81f * Time::deltaTime;

	//glm::vec2 currentPosition = Position;
	//glm::vec2 targetPosition = currentPosition + vel;

	//glm::ivec2 lastStep = currentPosition;

	//int cX = currentPosition.x;
	//int cY = currentPosition.y;

	//int tX = targetPosition.x;
	//int tY = targetPosition.y;

	//int xDiff = tX - cX;
	//int yDiff = tY - cY;

	//bool xDiffIsLarger = glm::abs(xDiff) > glm::abs(yDiff);

	//int xMod = xDiff > 0 ? 1 : -1;
	//int yMod = yDiff > 0 ? 1 : -1;

	//int longerSideLength = std::max(glm::abs(xDiff), glm::abs(yDiff));
	//int shorterSideLength = std::min(glm::abs(xDiff), glm::abs(yDiff));

	//float slope = (shorterSideLength == 0 || longerSideLength == 0) ? 0 : ((float)(shorterSideLength) / (longerSideLength));

	//int shorterSideIncrease;

	//for (int i = 1; i <= longerSideLength; i++)
	//{
	//	shorterSideIncrease = glm::round(i * slope);
	//	int yIncrease, xIncrease;
	//	if (xDiffIsLarger)
	//	{
	//		xIncrease = i;
	//		yIncrease = shorterSideIncrease;
	//	}
	//	else
	//	{
	//		yIncrease = i;
	//		xIncrease = shorterSideIncrease;
	//	}

	//	int stepY = cY + (yIncrease * yMod);
	//	int stepX = cX + (xIncrease * xMod);

	//	glm::ivec2 step = { stepX, stepY };

	//	Element* stepEle = world->GetElementAtWorldPos(step);

	//	if (stepEle != nullptr && stepEle->ID == 0)
	//	{
	//		Velocity = vel;
	//		world->SetElementAtWorldPos(lastStep, stepEle);
	//		world->SetElementAtWorldPos(step, this);
	//		lastStep = step;
	//	}
	//	else
	//	{
	//		Velocity = { 0, 0 };

	//		if (rand() % 2)
	//		{
	//			Element* elementBR = world->GetElementAtWorldPos(lastStep + glm::ivec2(1, -1));
	//			if (elementBR != nullptr && elementBR->ID == 0)
	//			{
	//				world->SetElementAtWorldPos(lastStep, elementBR);
	//				world->SetElementAtWorldPos(lastStep + glm::ivec2(1, -1), this);
	//			}
	//		}
	//		else
	//		{
	//			Element* elementBL = world->GetElementAtWorldPos(lastStep + glm::ivec2(-1, -1));
	//			if (elementBL != nullptr && elementBL->ID == 0)
	//			{
	//				world->SetElementAtWorldPos(lastStep, elementBL);
	//				world->SetElementAtWorldPos(lastStep + glm::ivec2(-1, -1), this);
	//			}
	//		}
	//		break;
	//	}



	//	//Element* stepEle = world->GetElementAtWorldPos(step);
	//	//if (stepEle == nullptr) return;
	//	//if (stepEle->ID == 0)
	//	//{
	//	//	Velocity = vel;
	//	//	world->SetElementAtWorldPos(lastStep, stepEle);
	//	//	world->SetElementAtWorldPos(step, this);
	//	//	lastStep = step;
	//	//}
	//	//else
	//	//{
	//	//	Velocity = { 0, 0 };
	//	//	Element* elementB = world->GetElementAtWorldPos(step + glm::ivec2(0, -1));
	//	//	Element* elementBR = world->GetElementAtWorldPos(step + glm::ivec2(1, -1));
	//	//	Element* elementBL = world->GetElementAtWorldPos(step + glm::ivec2(-1, -1));
	//	//	if (elementB != nullptr && elementB->ID == 0)
	//	//	{
	//	//		world->SetElementAtWorldPos(step, elementB);
	//	//		world->SetElementAtWorldPos(step + glm::ivec2(0, -1), stepEle);
	//	//	}
	//	//	else if (elementBR != nullptr && elementBR->ID == 0)
	//	//	{
	//	//		world->SetElementAtWorldPos(step, elementBR);
	//	//		world->SetElementAtWorldPos(step + glm::ivec2(1, -1), stepEle);
	//	//	}
	//	//	else if (elementBL != nullptr && elementBL->ID == 0)
	//	//	{
	//	//		world->SetElementAtWorldPos(step, elementBL);
	//	//		world->SetElementAtWorldPos(step + glm::ivec2(-1, -1), stepEle);
	//	//	}
	//	//	break;
	//	//}
	//}

bool Cell::MoveDown(Chunk* c)
{

	int x = position.x;
	int y = position.y;
	int tX = x;
	int tY = y - 1;

	Cell dst = c->GetCell(tX, tY);
	if (dst.id == 0)
	{
		c->MoveCell(x, y, tX, tY);
		return true;
	}

	return false;
}
