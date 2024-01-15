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

	bool active = false;
};

const Cell VOID =		{ 255, { 0.0f, 0.0f, 0.0f, 0.0f } };

const Cell AIR =		{ 0, { 0.1f, 0.1f, 0.1f, 1.0f } };
const Cell STONE =		{ 1, { 0.5f, 0.5f, 0.5f, 1.0f } };
const Cell DIRT =		{ 2, { 0.5f, 0.5f, 0.5f, 1.0f } };
const Cell SAND =		{ 3, { 0.9f, 0.7f, 0.2f, 1.0f } };

const Cell WATER =		{ 4, { 0.2f, 0.5f, 0.8f, 1.0f } };
const Cell LAVA =		{ 5, { 0.9f, 0.2f, 0.2f, 1.0f } };

//const Cell FIRE =		{ , { 0.9f, 0.2f, 0.2f, 1.0f } };
//const Cell SMOKE =	{ , { 0.2f, 0.2f, 0.2f, 1.0f } };
//const Cell STEAM =	{ , { 0.2f, 0.2f, 0.2f, 1.0f } };
//
//const Cell LOG =		{ , { 0.4f, 0.2f, 0.1f, 1.0f } };
//const Cell LEAVES =	{ , { 0.1f, 0.5f, 0.1f, 1.0f } };
//const Cell STEM =		{ , { 0.3f, 0.6f, 0.3f, 1.0f } };

const glm::ivec2 NeighbourTable[8] = {
	glm::ivec2( 0, -1), // Bot
	glm::ivec2(-1, -1), // Bot Left
	glm::ivec2( 1, -1), // Bot Right
	glm::ivec2(-1,  0), // Left
	glm::ivec2( 1,  0), // Right
	glm::ivec2(-1,  1), // Top Left
	glm::ivec2( 0,  1), // Top
	glm::ivec2( 1,  1), // Top Right
};

const glm::ivec2 NeighbourTable2[9] = {
	glm::ivec2(-1,  1), // Top Left
	glm::ivec2(0,  1), // Top
	glm::ivec2(1,  1), // Top Right

	glm::ivec2(-1,  0), // Left
	glm::ivec2(0, 0), // Center
	glm::ivec2(1,  0), // Right

	glm::ivec2(-1, -1), // Bot Left
	glm::ivec2(0, -1), // Bot
	glm::ivec2(1, -1), // Bot Right
};

const glm::vec3 vertexPositions[] = {
	glm::vec3( 0.0f, 0.0f, 0.0f ),
	glm::vec3( 0.0f, 1.0f, 0.0f ),
	glm::vec3( 1.0f, 0.0f, 0.0f ),
	glm::vec3( 1.0f, 1.0f, 0.0f ),
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






// Cell Interaction types
// Swap
// Interact


