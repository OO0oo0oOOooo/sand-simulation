#pragma once

#include <array>
#include <functional>

#pragma region Step Functions
extern void AirStep();
extern void StoneStep();
extern void DirtStep();
extern void SandStep();
extern void WaterStep();
extern void LavaStep();
#pragma endregion

#pragma region Act On Other Functions
extern void AirActOnOther();
extern void StoneActOnOther();
extern void DirtActOnOther();
extern void SandActOnOther();
extern void WaterActOnOther();
extern void LavaActOnOther();
#pragma endregion

extern std::array<std::function<void()>, 255> StepFuncTable;
extern std::array<std::function<void()>, 255> ActOnOtherFuncTable;