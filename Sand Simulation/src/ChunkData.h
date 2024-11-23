#pragma once

const int WORLD_WIDTH = 6;
const int WORLD_HEIGHT = 3;

const int CHUNK_WIDTH = 64;
const int CHUNK_HEIGHT = 64;
const int CHUNK_SIZE = 4096;

const int WORLD_WIDTH_IN_CELLS = WORLD_WIDTH * CHUNK_WIDTH;
const int WORLD_HEIGHT_IN_CELLS = WORLD_HEIGHT * CHUNK_HEIGHT;

const int CELL_SIZE_IN_PIXELS = 5;

// Todo: Delete this when world and chunk are written
//const int numChunksWidth = 6;
//const int numChunksHeight = 3;
//
//const int chunkSizeInCells = 64;
//const int cellSize = 5;

//const glm::vec2 worldSizeInCells = glm::vec2(numChunksWidth * chunkSizeInCells, numChunksHeight * chunkSizeInCells);