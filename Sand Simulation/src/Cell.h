#pragma once

#include "ParticleData.h"
#include "Renderer.h"
#include "Grid.h"

class Cell
{
public:
	Cell();
	Cell(unsigned char Id);

	~Cell();

	void CheckBounds();
	void Update();
	void Render();

	Grid* Grid;

	unsigned char Id;
	glm::vec4 Color;
	glm::vec2 Velocity;

	unsigned int LifeTime;

	int Temperature;
	int Conductivity;
	int Moisture;
	int HeatCapacity;
	int Density;
	int Hardness;
	int Weight;
	
	int BoilingPoint;
	int MeltingPoint;
	int FreezingPoint;

	int IgnitionPoint;
	int FlashPoint;
	int ExplosionPoint;

	unsigned int Flammability;
	unsigned int Explosiveness;

	bool IsSolid;
	bool IsLiquid;
	bool IsGas;

	void UpdateProperties();
	void UpdateColor();
	void UpdateVelocity();
	void UpdateTemperature();
	void UpdateState();
	void UpdateLifeTime();

private:
	
};