#include "Cell.h"
// #include "Chunk.h"
// #include <vector>
// #include <functional>

// template<typename... Args>
// void LineSolver(glm::ivec2 start, glm::ivec2 end, const std::function<void(Args...)> f)
// {
// 	int cX = start.x;
// 	int cY = start.y;
// 	int tX = end.x;
// 	int tY = end.y;
//
// 	int xDiff = tX - cX;
// 	int yDiff = tY - cY;
//
// 	bool xDiffIsLarger = glm::abs(xDiff) > glm::abs(yDiff);
// 	int xMod = xDiff > 0 ? 1 : -1;
// 	int yMod = yDiff > 0 ? 1 : -1;
//
// 	int longerSideLength = std::max(glm::abs(xDiff), glm::abs(yDiff));
// 	int shorterSideLength = std::min(glm::abs(xDiff), glm::abs(yDiff));
//
// 	float slope = (shorterSideLength == 0 || longerSideLength == 0) ? 0 : ((float)(shorterSideLength) / (longerSideLength));
// 	int shorterSideIncrease;
//
// 	for (int i = 1; i <= longerSideLength; i++)
// 	{
// 		shorterSideIncrease = glm::round(i * slope);
// 		int yIncrease, xIncrease;
// 		if (xDiffIsLarger)
// 		{
// 			xIncrease = i;
// 			yIncrease = shorterSideIncrease;
// 		}
// 		else
// 		{
// 			yIncrease = i;
// 			xIncrease = shorterSideIncrease;
// 		}
//
// 		int stepY = cY + (yIncrease * yMod);
// 		int stepX = cX + (xIncrease * xMod);
//
// 		glm::ivec2 step = { stepX, stepY };
// 	}
// }
//
// std::vector<glm::ivec2> LineSolver(glm::ivec2 start, glm::ivec2 end)
// {
// 	std::vector<glm::ivec2> points;
//
// 	int cX = start.x;
// 	int cY = start.y;
// 	int tX = end.x;
// 	int tY = end.y;
//
// 	int xDiff = tX - cX;
// 	int yDiff = tY - cY;
//
// 	bool xDiffIsLarger = glm::abs(xDiff) > glm::abs(yDiff);
// 	int xMod = xDiff > 0 ? 1 : -1;
// 	int yMod = yDiff > 0 ? 1 : -1;
//
// 	int longerSideLength = std::max(glm::abs(xDiff), glm::abs(yDiff));
// 	int shorterSideLength = std::min(glm::abs(xDiff), glm::abs(yDiff));
//
// 	float slope = (shorterSideLength == 0 || longerSideLength == 0) ? 0 : ((float)(shorterSideLength) / (longerSideLength));
// 	int shorterSideIncrease;
//
// 	for (int i = 1; i <= longerSideLength; i++)
// 	{
// 		shorterSideIncrease = glm::round(i * slope);
// 		int yIncrease, xIncrease;
// 		if (xDiffIsLarger)
// 		{
// 			xIncrease = i;
// 			yIncrease = shorterSideIncrease;
// 		}
// 		else
// 		{
// 			yIncrease = i;
// 			xIncrease = shorterSideIncrease;
// 		}
//
// 		int stepY = cY + (yIncrease * yMod);
// 		int stepX = cX + (xIncrease * xMod);
//
// 		glm::ivec2 step = { stepX, stepY };
//
// 		points.push_back(step);
// 	}
//
// 	return points;
// }
//
// void SandStep(Chunk* chunk, Cell cell)
// {
// 	if (cell.id != 3) return;
//
// 	int x = cell.position.x;
// 	int y = cell.position.y;
//
// 	Cell below = chunk->GetCell(x, y - 1);
// 	Cell left  = chunk->GetCell(x - 1, y);
// 	Cell right = chunk->GetCell(x + 1, y);
// 	Cell bleft = chunk->GetCell(x - 1, y - 1);
// 	Cell bright = chunk->GetCell(x + 1, y - 1);
//
// 	if (below.id == 0)
// 	{
// 		cell.velocity.y++;
// 		chunk->SetCell(x, y, below);
// 		chunk->SetCell(x, y - 1, cell);
// 		return;
// 	}
// 	else if (left.id == 0 && bleft.id == 0)
// 	{
// 		cell.velocity.x--;
// 		chunk->SetCell(x, y, bleft);
// 		chunk->SetCell(x - 1, y - 1, cell);
// 		return;
// 	}
// 	else if (right.id == 0 && bright.id == 0)
// 	{
// 		cell.velocity.x++;
// 		chunk->SetCell(x, y, bright);
// 		chunk->SetCell(x + 1, y - 1, cell);
// 		return;
// 	}
// }
//
// bool Cell::MoveDown(Chunk* c)
// {
// 	int x = position.x;
// 	int y = position.y;
// 	int tX = x;
// 	int tY = y - 1;
//
// 	Cell dst = c->GetCell(tX, tY);
// 	if (dst.id == 0)
// 	{
// 		c->MoveCell(x, y, tX, tY);
// 		return true;
// 	}
//
// 	return false;
// }
