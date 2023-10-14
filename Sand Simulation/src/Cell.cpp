#include "Cell.h"


Cell::Cell()
{
}

Cell::~Cell()
{
}

void Cell::Update()
{
	switch (Id)
	{
	case 0:
		break;

	case 1:
		break;

	case 2:
		UpdateSand();
		break;


	default:
		break;
	}
}


void Cell::UpdateSand(int x, int y)
{

	if (y < 0)
		return;

	if (Id == ParticleSand.type)
	{

		if (GetParticle(x, y - 1).type == ParticleAir.type)
		{
			SetParticle(x, y, ParticleAir);
			SetParticle(x, y - 1, ParticleSand);
		}
		else if (GetParticle(x + 1, y - 1).type == ParticleAir.type)
		{
			SetParticle(x, y, ParticleAir);
			SetParticle(x + 1, y - 1, ParticleSand);
		}
		else if (GetParticle(x - 1, y - 1).type == ParticleAir.type)
		{
			SetParticle(x, y, ParticleAir);
			SetParticle(x - 1, y - 1, ParticleSand);
		}

	}
}
//void UpdateGunpowder(Renderer* renderer, int x, int y);
//
//void UpdateStone(Renderer* renderer, int x, int y);
//void UpdateWood(Renderer* renderer, int x, int y);
//
//void UpdateWater(Renderer* renderer, int x, int y);
//void UpdateOil(Renderer* renderer, int x, int y);
//void UpdateLava(Renderer* renderer, int x, int y);
//void UpdateAcid(Renderer* renderer, int x, int y);
//
//void UpdateSmoke(Renderer* renderer, int x, int y);
//void UpdateSteam(Renderer* renderer, int x, int y);
//
//void UpdateFire(Renderer* renderer, int x, int y);
//
//void UpdateCloud(Renderer* renderer, int x, int y);