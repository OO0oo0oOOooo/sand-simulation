#include "World.h"
#include "Elements/Element.h"
#include "Elements/Empty.h"
#include "Elements/Water.h"
#include "Elements/Sand.h"
#include "Elements/Air.h"

void CellularAutomata(int id, Chunk* chunk)
{
	chunk->Update();
}

void World::Update(Shader* shader)
{
	std::vector<Chunk*> chunksToUpdate;

	for (int pass = 0; pass < 4; ++pass)
	{
		std::vector<std::pair<std::future<void>, Chunk*>> futures;

		for (int y = 0; y < numChunksHeight; y++)
		{
			for (int x = 0; x < numChunksWidth; x++)
			{
				if ((x + y + pass) % 4 == 0)
				{
					Chunk* chunk = _chunks[{x, y}];

					if (chunk != nullptr)
					{
						futures.push_back(std::make_pair(_threadPool->push(CellularAutomata, chunk), chunk));
					}
				}

			}
		}

		for (auto& f : futures)
		{
			f.first.get();
			chunksToUpdate.push_back(f.second);
		}
	}

	for (Chunk* chunk : chunksToUpdate)
	{
		chunk->UploadMeshData();
		chunk->DrawMesh(shader);
	}
}

void World::EditElementAtPixel(glm::vec2 position, int element)
{
	if (position.x < 0 || position.x > 1920 || position.y < 0 || position.y > 1080)
		return;

	glm::ivec2 cellPos = PixelToCellPos(position);
	Chunk* chunk = GetChunkFromWorldPos(cellPos);

	if (chunk == nullptr)
		return;

	switch (element)
	{
	case 0:
		chunk->SetElementAtWorldPosition(cellPos, new Air({ cellPos.x, cellPos.y }));
		break;

	case 3:
		chunk->SetElementAtWorldPosition(cellPos, new Sand({ cellPos.x, cellPos.y }));
		break;
	}


}

void World::MoveElement(glm::ivec2 from, glm::ivec2 to)
{
	Element* element = GetElementAtWorldPos(from);

	if (element == nullptr)
		return;

	SetElementAtWorldPos(from, new Air(from));
	SetElementAtWorldPos(to, element);
}

void World::SwapElements(glm::ivec2 oldPos, glm::ivec2 newPos)
{
	Element* element1 = GetElementAtWorldPos(oldPos);
	Element* element2 = GetElementAtWorldPos(newPos);

	if (element1 == nullptr || element2 == nullptr)
		return;

	SetElementAtWorldPos(oldPos, element2);
	SetElementAtWorldPos(newPos, element1);
}