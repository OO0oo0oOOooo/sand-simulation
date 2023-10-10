struct Particle
{
	unsigned char type;
	glm::vec4 color;
	//glm::vec3 velocity;

	//unsigned int Temperature;

	//unsigned int Conductivity;
	//unsigned int Flammability;

	//unsigned int GasTemp;
	//unsigned int LiquidTemp;
	//unsigned int FreezingTemp;

	//unsigned int Density;
	//unsigned int Viscosity;
	//unsigned int Hardness;
};



//namespace ParticleTypes
//{
//	enum ParticleType
//	{
//		Air,
//		Sand,
//		Water,
//		Rock,
//		Wood,
//		Metal,
//		Gunpowder,
//		Fire,
//		Smoke,
//		Steam,
//		Lava,
//		Oil,
//		Acid,
//		Glass,
//		Ice
//	};
//
//	Particle ParticleAir = { 0, { 0.0f, 0.0f, 0.0f, 1.0f }, {0.0f, 0.0f, 0.0f}, 0, 0, 0, 0, 0, 0, 0};
//	Particle ParticleSand = { 1,{ 0.9f, 0.8f, 0.2f, 1.0f }, {0.0f, 0.0f, 0.0f}, 0, 0, 0, 0, 0, 0, 0};
//}


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

// Type 0 = Air
// Type 1 = Sand
// Type 2 = Water
// Type 3 = Rock
// Type 4 = Wood
// Type 5 = Metal
// Type 6 = Gunpowder
// Type 7 = Fire

// Smoke
// Steam
// Lava
// Oil
// Acid
// Glass
// Ice

// Elemental Particles
// Frost
// Heat
// Shock


// Sand/Glass -> Molten Glass
// Ice -> Water -> Steam
// Rock -> Lava


