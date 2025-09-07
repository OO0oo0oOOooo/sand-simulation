#pragma once

#include "Core/Scene.h"
#include "Core/ComponentRegistry.h"
#include "Core/Components/Renderable.h"
#include "Core/Components/Transform.h"
#include "Rendering/ResourceHandle.h"
#include "Rendering/ResourceManager.h"
#include "../SandSimulation.h"

inline void update_dirty_chunks(Scene* scene) {
    for (uint32_t entity : scene->m_Registry.m_Entities) {
        chunk* chunk_c = scene->m_Registry.GetComponent<chunk>(entity);
        transform* transform_c = scene->m_Registry.GetComponent<transform>(entity);
        renderable* renderable_c = scene->m_Registry.GetComponent<renderable>(entity);
        // chunk* chunk_c = scene->GetComponent<chunk>(entity, "chunk");
        // transform* transform_c = scene->GetComponent<transform>(entity, "transform");
        // renderable* renderable_c = scene->GetComponent<renderable>(entity, "renderable");

        if (chunk_c && transform_c && renderable_c) {
            if (chunk_c->isDirty) {
                chunk_c->isDirty = false;
                ResourceManager* rm = ResourceManager::GetResourceManager();
                resource_handle texture_handle = rm->GetMaterial(renderable_c->material_handle)->texture_handle;
                texture* tex = rm->GetTexture(texture_handle);

                int xOffset = transform_c->position.x;
                int yOffset = transform_c->position.y;
                texture_update_subdata(tex, (uint8_t*)chunk_c->pixels, 64, 64, xOffset, yOffset);
            }
        }
    }
}
