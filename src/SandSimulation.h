#pragma once

#include <cstring>
#include <sstream>
#include <fstream>

inline int get_index(int width, int x, int y) {
    int nx = ((x % 64) + 64) % 64;
    int ny = ((y % 64) + 64) % 64;
    return ny * width + nx;
}

inline int get_x(int index, int width) {
    return index % width;
}

inline int get_y(int index, int width) {
    return index / width;
}

struct cell {
    uint8_t type = 0;
};

struct chunk {
    cell cells[256];
};

struct world {
    size_t width;
    size_t height;
    size_t chunk_width;
    std::vector<chunk> chunks;
};

inline void world_load(std::string line, void* buffer) {
    world w {};

    std::stringstream ss(line);
    std::string type;
    ss >> type >> w.width >> w.height;

    memcpy(buffer, &w, sizeof(world));
}

inline void world_save(const void* data, std::ofstream& file) {
    const world* w = static_cast<const world*>(data);

    file << "World " << w->width << " " << w->height << "\n";
}
