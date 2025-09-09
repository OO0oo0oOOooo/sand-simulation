#include "Engine.h"
#include "Rendering/ResourceManager.h"
#include "Core/Systems/EngineRenderSystems.h"
#include "src/Systems/GameUpdateSystems.h"
#include "SandSimulation.h"

int main() {
    Application app;
    Scene* scene = app.GetScene();

    scene->m_ComponentRegistry.RegisterComponent<transform>(sizeof(transform), transform_save, transform_load);
    scene->m_ComponentRegistry.RegisterComponent<renderable>(sizeof(renderable), renderable_save, renderable_load);
    scene->m_ComponentRegistry.RegisterComponent<camera>(sizeof(camera), nullptr, nullptr);
    scene->m_ComponentRegistry.RegisterComponent<world>(sizeof(world), nullptr, nullptr);
    scene->m_ComponentRegistry.RegisterComponent<chunk>(sizeof(chunk), nullptr, nullptr);

    scene->m_SystemRegistry.AddRenderSystem(default_render);
    scene->m_SystemRegistry.AddUpdateSystem(update_dirty_chunks);

    resource_handle shader_handle = ResourceManager::LoadShader("default_shader");
    resource_handle texture_handle = ResourceManager::CreateTexture(64 * 4, 64 * 4);
    resource_handle material_handle = ResourceManager::CreateMaterial(shader_handle, texture_handle);

    size_t width = 4;
    size_t height = 4;
    size_t area = width * height;
    size_t w = 64;

    world world_c{
        .width = width,
        .height = height,
        .chunk_width = w,
    };

    camera camera_c{};
    camera_c = camera_init({0, 0, 0}, {1, 0, 0, 0}, 256, 256, -1.0f, 1.0f);

    uint32_t entity = scene->m_ComponentRegistry.CreateEntity();
    scene->m_ComponentRegistry.AddComponent<transform>(entity, transform{});
    scene->m_ComponentRegistry.AddComponent<camera>(entity, camera_c);
    scene->m_ComponentRegistry.AddComponent<world>(entity, world_c);

    scene->m_ActiveCamera = scene->m_ComponentRegistry.GetComponent<camera>(entity);
    SystemEvents::listen(EVENT_WINDOW_RESIZE, set_window_size, scene->m_ActiveCamera);

    for (int i = 0; i < area; i++) {
        int x = get_x(i, width);
        int y = get_y(i, width);

        float uv_x = x * 0.25;
        float uv_y = y * 0.25;
        float uv_size = 0.25;

        Vertex v1{{0, 0, 0}, {0, 0, 1, 1}, {uv_x, uv_y}};
        Vertex v2{{0, w, 0}, {0, 1, 0, 1}, {uv_x, uv_y + uv_size}};
        Vertex v3{{w, 0, 0}, {1, 0, 0, 1}, {uv_x + uv_size, uv_y}};
        Vertex v4{{w, w, 0}, {1, 1, 0, 1}, {uv_x + uv_size, uv_y + uv_size}};

        resource_handle mesh_handle = ResourceManager::CreateMesh({v1, v2, v3, v4}, {0, 1, 2, 2, 1, 3});

        chunk chunk_c{};
        chunk_init(chunk_c);

        uint32_t entity = scene->m_ComponentRegistry.CreateEntity();
        scene->m_ComponentRegistry.AddComponent<transform>(entity, transform{.position = {x * w, y * w, 0}});
        scene->m_ComponentRegistry.AddComponent<renderable>(entity, renderable{mesh_handle, material_handle});
        scene->m_ComponentRegistry.AddComponent<chunk>(entity, chunk_c);
    }

    app.Run();
}
