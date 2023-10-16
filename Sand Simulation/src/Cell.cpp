#include "Cell.h"

Cell::Cell()
{
}

Cell::Cell(Grid* grid, unsigned char id)
{
	m_Grid = grid;

	Id = id;
	Color = particleColors[id];
	Velocity = glm::vec2(0.0f, 0.0f);

	LifeTime = 0;

	Temperature = 0;
	Conductivity = 0;
	Moisture = 0;
	HeatCapacity = 0;
	Density = 0;
	Hardness = 0;
	Weight = 0;

	BoilingPoint = 0;
	MeltingPoint = 0;
	FreezingPoint = 0;

	IgnitionPoint = 0;
	FlashPoint = 0;
	ExplosionPoint = 0;

	Flammability = 0;
	Explosiveness = 0;

	IsSolid = false;
	IsLiquid = false;
	IsGas = false;
}

Cell::~Cell()
{
}

void Cell::Update()
{
	switch (Id)
	{
	case 0:
		// UpdateVoid();
		break;

	case 1:
		// UpdateAir();
		break;

	case 2:
		// UpdateSand();
		break;


	default:
		break;
	}
}


//void UpdateSand(int x, int y)
//{
//
//	if (y < 0)
//		return;
//
//	if (Cell::Id == ParticleSand.type)
//	{
//
//		if (Cell::m_Grid->GetCell(x, y - 1).type == ParticleAir.type)
//		{
//			SetParticle(x, y, ParticleAir);
//			SetParticle(x, y - 1, ParticleSand);
//		}
//		else if (GetParticle(x + 1, y - 1).type == ParticleAir.type)
//		{
//			SetParticle(x, y, ParticleAir);
//			SetParticle(x + 1, y - 1, ParticleSand);
//		}
//		else if (GetParticle(x - 1, y - 1).type == ParticleAir.type)
//		{
//			SetParticle(x, y, ParticleAir);
//			SetParticle(x - 1, y - 1, ParticleSand);
//		}
//
//	}
//}

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