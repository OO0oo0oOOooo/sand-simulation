#include "CellCommands.h"
#include <iostream>

#pragma region Step Functions
void AirStep()
{
	return;
}

void StoneStep()
{
	return;
}

void DirtStep()
{
	return;
}

void SandStep()
{
	//std::cout << "Sand Step" << std::endl;

	//glm::vec2 start(pos);
	//glm::vec2 target(pos.x, pos.y - 1);

	//if (a.id == 3 && b.id == 0)
	//{
	//	SetCell(x, y - 1, a);
	//	SetCell(x, y, b);
	//}
}

void WaterStep()
{
	return;
}

void LavaStep()
{
	return;
}
#pragma endregion

#pragma region Act On Other Functions
void AirActOnOther()
{
	return;
}

void StoneActOnOther()
{
	return;
}

void DirtActOnOther()
{
	return;
}

void SandActOnOther()
{
	return;
}

void WaterActOnOther()
{
	return;
}

void LavaActOnOther()
{
	return;
}
#pragma endregion

std::array<std::function<void()>, 255> StepFuncTable =
{
	AirStep,
	StoneStep,
	DirtStep,
	SandStep,
	WaterStep,
	LavaStep,
};

std::array<std::function<void()>, 255> ActOnOtherFuncTable =
{
	AirActOnOther,
	StoneActOnOther,
	DirtActOnOther,
	SandActOnOther,
	WaterActOnOther,
	LavaActOnOther,
};