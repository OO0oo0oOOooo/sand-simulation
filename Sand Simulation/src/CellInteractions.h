#pragma once
#include <map>

int SandAir[] = { 0, 3 };
int SandWater[] = { 4, 3 };

int WaterAir[] = { 0, 4 };
int WaterLava[] = { 0, 1 };

int LavaAir[] = { 0, 5 };

int STEAMAIR[] = { 0, 6 };

std::map<int, std::map<int, std::map<int, int*>>> LUT = {
	{3, {
		{0, {
			{0, SandAir},
			{1, SandAir},
			{2, SandAir},
		}},

		{4, {
			{0, SandWater},
			{1, SandWater},
			{2, SandWater},
		}},
	}},

	{4, {
		{0, {
			{0, WaterAir},
			{1, WaterAir},
			{2, WaterAir},
			{3, WaterAir},
			{4, WaterAir},
		}},

		{5, {
			{0, WaterLava},
			{3, WaterLava},
			{4, WaterLava},
			{6, WaterLava},

		}},
	}},

	{5, {
		{0, {
			{0, LavaAir},
			{3, LavaAir},
			{4, LavaAir},
		}},
	}},

	{6, {
		{0, {
			{5, STEAMAIR},
			{6, STEAMAIR},
			{7, STEAMAIR},
		}},
	}},
};