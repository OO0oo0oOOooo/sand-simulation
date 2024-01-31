#pragma once

const int numChunksWidth = 6;
const int numChunksHeight = 3;

const int chunkSizeInCells = 64;
const int cellSize = 5;

const glm::vec2 worldSizeInCells = glm::vec2(numChunksWidth * chunkSizeInCells, numChunksHeight * chunkSizeInCells);