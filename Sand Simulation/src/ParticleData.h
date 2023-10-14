#pragma once

#include <glm/glm.hpp>

struct Particle
{
	unsigned char type;
	glm::vec4 color;
	//glm::vec3 velocity;

	//unsigned int Temperature;

	//unsigned int Conductivity;
	//unsigned int Flammability;
	//unsigned int Hardness;
	//unsigned int Density;
	//unsigned int Buoyancy;

	//unsigned int GasTemp;
	//unsigned int LiquidTemp;
	//unsigned int FreezingTemp;
};

enum ParticleSelection
{
	Void = 0,
	Air,
	Sand,
	Water,
	Rock,
	Wood,
	Metal,
	Gunpowder,
	Fire,
	Smoke,
	Steam,
};

const Particle ParticleVoid =      { 0, { 0.0f, 0.0f, 0.0f, 0.0f } };
const Particle ParticleAir =       { 1, { 0.1f, 0.1f, 0.1f, 1.0f } };
const Particle ParticleSand =      { 2, { 0.9f, 0.7f, 0.2f, 1.0f } };
const Particle ParticleWater =     { 3, { 0.2f, 0.5f, 0.8f, 1.0f } };
const Particle ParticleRock =      { 4, { 0.5f, 0.5f, 0.5f, 1.0f } };
const Particle ParticleWood =	   { 5, { 0.4f, 0.2f, 0.1f, 1.0f } };
const Particle ParticleMetal =     { 6, { 0.3f, 0.3f, 0.3f, 1.0f } };
const Particle ParticleGunpowder = { 7, { 0.2f, 0.2f, 0.2f, 1.0f } };

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

//glm::vec4 debugColors[] = {
//	glm::vec4(0.9f, 0.8f, 0.2f, 1.0f),
//	glm::vec4(0.9f, 0.2f, 0.8f, 1.0f),
//	glm::vec4(0.2f, 0.9f, 0.8f, 1.0f),
//	glm::vec4(0.5f, 0.2f, 0.5f, 1.0f),
//};

//glm::vec4 c_Air =   glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
//glm::vec4 c_Sand =  glm::vec4(0.9f, 0.8f, 0.2f, 1.0f);
//glm::vec4 c_Water = glm::vec4(0.2f, 0.9f, 0.8f, 1.0f);
//glm::vec4 c_Rock =  glm::vec4(0.5f, 0.2f, 0.5f, 1.0f);
//glm::vec4 c_Wood =  glm::vec4(0.4f, 0.2f, 0.1f, 1.0f);
//glm::vec4 c_Fire =  glm::vec4(0.9f, 0.2f, 0.2f, 1.0f);
//glm::vec4 c_Smoke = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
//glm::vec4 c_Steam = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
//glm::vec4 c_Lava = glm::vec4(0.9f, 0.2f, 0.2f, 1.0f);
//glm::vec4 c_Oil = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
//glm::vec4 c_Acid = glm::vec4(0.2f, 0.8f, 0.2f, 1.0f);
//glm::vec4 c_Glass = glm::vec4(0.2f, 0.2f, 0.2f, 0.5f);
//glm::vec4 c_Ice = glm::vec4(0.2f, 0.2f, 0.8f, 0.5f);

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


