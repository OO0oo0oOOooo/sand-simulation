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
    uint32_t color = { 0xFFFFFFFF };
};

struct chunk {
    cell cells[4096];
    uint32_t pixels[4096];
    bool isDirty = true;
};

inline void chunk_init(chunk& c) {
    for (int i = 0; i < 4096; i++) {
        c.pixels[i] = c.cells[i].color;
    }

    c.isDirty = true;
}

struct world {
    size_t width;
    size_t height;
    size_t chunk_width;
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
