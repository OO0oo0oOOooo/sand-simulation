#pragma once

#include "Core/ComponentRegistry.h"
#include "Core/Components/Renderable.h"
#include "Core/Components/Transform.h"
#include "Rendering/ResourceHandle.h"
#include "Rendering/ResourceManager.h"
#include "../SandSimulation.h"

inline void update_dirty_chunks(ComponentRegistry& registry) {
    for (uint32_t entity : registry.m_Entities) {
        chunk* chunk_c = registry.GetComponent<chunk>(entity);
        transform* transform_c = registry.GetComponent<transform>(entity);
        renderable* renderable_c = registry.GetComponent<renderable>(entity);

        if (chunk_c && transform_c && renderable_c) {
            if (chunk_c->isDirty) {
                chunk_c->isDirty = false;
                resource_handle texture_handle = ResourceManager::GetMaterial(renderable_c->material_handle)->texture_handle;
                texture* tex = ResourceManager::GetTexture(texture_handle);

                int xOffset = transform_c->position.x;
                int yOffset = transform_c->position.y;
                texture_update_subdata(tex, (uint8_t*)chunk_c->pixels, 64, 64, xOffset, yOffset);
            }
        }
    }
}
