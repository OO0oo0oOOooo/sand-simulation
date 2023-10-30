#pragma once

#include <glm/glm.hpp>

struct Cell
{
	unsigned char Id;
	glm::vec4 color;

	glm::vec2 position = { 0, 0 };
	glm::vec2 velocity = { 0, 0 };
	int mass = 0;

	float lifeTime = 0;

	int temperature = 0;
	int conductivity = 0;
	int flammability = 0;
	int explosiveness = 0;

	char lightLevel = 0;

	bool dirty = true;
};

const glm::vec4 particleColors[] = {
	{ 0.0f, 0.0f, 0.0f, 0.0f }, // Void
	{ 0.1f, 0.1f, 0.1f, 1.0f }, // Air
	{ 0.9f, 0.7f, 0.2f, 1.0f }, // Sand
	{ 0.2f, 0.5f, 0.8f, 1.0f }, // Water
	{ 0.5f, 0.5f, 0.5f, 1.0f }, // Rock
	{ 0.4f, 0.2f, 0.1f, 1.0f }, // Wood
	{ 0.3f, 0.3f, 0.3f, 1.0f }, // Metal
	{ 0.2f, 0.2f, 0.2f, 1.0f }, // Gunpowder
	{ 0.9f, 0.2f, 0.2f, 1.0f }, // Fire
	{ 0.2f, 0.2f, 0.2f, 1.0f }, // Smoke
	{ 0.2f, 0.2f, 0.2f, 1.0f }, // Steam
};

const Cell ParticleVoid =      { 0, { 0.0f, 0.0f, 0.0f, 0.0f } };
const Cell ParticleAir =       { 1, { 0.1f, 0.1f, 0.1f, 1.0f } };
const Cell ParticleSand =      { 2, { 0.9f, 0.7f, 0.2f, 1.0f } };
const Cell ParticleWater =     { 3, { 0.2f, 0.5f, 0.8f, 1.0f } };
const Cell ParticleRock =      { 4, { 0.5f, 0.5f, 0.5f, 1.0f } };
const Cell ParticleWood =	   { 5, { 0.4f, 0.2f, 0.1f, 1.0f } };
const Cell ParticleMetal =     { 6, { 0.3f, 0.3f, 0.3f, 1.0f } };
const Cell ParticleGunpowder = { 7, { 0.2f, 0.2f, 0.2f, 1.0f } };

const glm::vec3 vertexPositions[] = {
	glm::vec3(-0.0f, -0.0f, 0.0f),
	glm::vec3(-0.0f,  1.0f, 0.0f),
	glm::vec3( 1.0f, -0.0f, 0.0f),
	glm::vec3( 1.0f,  1.0f, 0.0f),
};

const unsigned int meshTriangles[] = {
	0, 1, 2,
	2, 1, 3,
};

// Main Particles

// Void
// Air
// Sand/Motlten Glass/Glass
// Dirt/Grass
// Ice/Water/Steam
// Rock/Lava
// Iron/Molten Iron
// Wood
// Gunpowder
// Fire

// Secondary Particles
// Foliage

// Smoke
// Steam
// Lava
// Oil
// Acid
// Glass
// Ice
// Obsidian

// Elemental Particles
// Frost
// Heat
// Shock

//class Cell
//{
//public:
//	Cell();
//	Cell(Grid* grid, unsigned char id);
//
//	~Cell();
//
//	void CheckBounds();
//	void Update();
//	void Render();
//
//	Grid* m_Grid;
//
//	unsigned char Id;
//	glm::vec4 Color;
//	glm::vec2 Velocity;
//
//	unsigned int LifeTime;
//
//	int Temperature;
//	int Conductivity;
//	int Moisture;
//	int HeatCapacity;
//	int Density;
//	int Hardness;
//	int Weight;
//	
//	int BoilingPoint;
//	int MeltingPoint;
//	int FreezingPoint;
//
//	int IgnitionPoint;
//	int FlashPoint;
//	int ExplosionPoint;
//
//	unsigned int Flammability;
//	unsigned int Explosiveness;
//
//	bool IsSolid;
//	bool IsLiquid;
//	bool IsGas;
//
//	void UpdateProperties();
//	void UpdateColor();
//	void UpdateVelocity();
//	void UpdateTemperature();
//	void UpdateState();
//	void UpdateLifeTime();
//
//private:
//	
//};