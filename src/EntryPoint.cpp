#include "Engine.h"
#include "SandSimulation.h"
#include "src/Systems/GameUpdateSystems.h"

int main() {
    Application app;
    Scene* scene = app.GetScene();
    ResourceManager* rm = ResourceManager::GetResourceManager();

    resource_handle shader_handle = rm->LoadShader("default_shader");
    resource_handle texture_handle = rm->CreateTexture(64 * 4, 64 * 4);
    resource_handle material_handle = rm->CreateMaterial(shader_handle, texture_handle);

    scene->m_Registry.RegisterComponent<transform>(sizeof(transform), transform_save, transform_load);
    scene->m_Registry.RegisterComponent<renderable>(sizeof(renderable), renderable_save, renderable_load);
    scene->m_Registry.RegisterComponent<camera>(sizeof(camera), nullptr, nullptr);
    scene->m_Registry.RegisterComponent<world>(sizeof(world), world_save, world_load);
    scene->m_Registry.RegisterComponent<chunk>(sizeof(chunk), world_save, world_load);
    // scene->m_Registry.RegisterComponent("transform", sizeof(transform), transform_save, transform_load);
    // scene->m_Registry.RegisterComponent("renderable", sizeof(renderable), renderable_save, renderable_load);
    // scene->m_Registry.RegisterComponent("camera", sizeof(camera), nullptr, nullptr);
    // scene->m_Registry.RegisterComponent("world", sizeof(world), world_save, world_load);
    // scene->m_Registry.RegisterComponent("chunk", sizeof(chunk), world_save, world_load);

    app.AddUpdateSystem(update_dirty_chunks);

    size_t width = 1;
    size_t height = 1;
    size_t area = width * height;
    size_t w = 64;

    world world_c {
        .width = width,
        .height = height,
        .chunk_width = w,
    };

    camera camera_c {};
    camera_c = camera_init({0,0,0}, {1,0,0,0}, 256, 256, -1.0f, 1.0f);

    uint32_t entity = scene->m_Registry.CreateEntity();
    scene->m_Registry.AddComponent<transform>(entity, transform{});
    scene->m_Registry.AddComponent<camera>(entity, camera_c);
    scene->m_Registry.AddComponent<world>(entity, world_c);
    // scene->AddComponent(entity, transform{}, "transform");
    // scene->AddComponent(entity, camera_c, "camera");
    // scene->AddComponent(entity, world_c, "world");

    // scene->m_ActiveCamera = scene->GetComponent<camera>(entity, "camera");
    scene->m_ActiveCamera = scene->m_Registry.GetComponent<camera>(entity);
    SystemEvents::listen(EVENT_WINDOW_RESIZE, set_window_size, scene->m_ActiveCamera);

    for (int i = 0; i < area; i++) {
        int x = get_x(i, width);
        int y = get_y(i, width);

        float uv_x = x * 0.25;
        float uv_y = y * 0.25;
        float uv_size = 0.25;

        Vertex v1 {{0, 0, 0}, {0, 0, 1, 1}, {uv_x, uv_y}};
        Vertex v2 {{0, w, 0}, {0, 1, 0, 1}, {uv_x, uv_y + uv_size}};
        Vertex v3 {{w, 0, 0}, {1, 0, 0, 1}, {uv_x + uv_size, uv_y}};
        Vertex v4 {{w, w, 0}, {1, 1, 0, 1}, {uv_x + uv_size, uv_y + uv_size}};

        resource_handle mesh_handle = rm->CreateMesh({v1, v2, v3, v4}, {0, 1, 2, 2, 1, 3});

        uint32_t entity = scene->m_Registry.CreateEntity();
        scene->m_Registry.AddComponent<transform>(entity, transform{ .position = {x * w, y * w, 0} });
        scene->m_Registry.AddComponent<renderable>(entity, renderable{ mesh_handle, material_handle });
        // scene->AddComponent(entity, transform{ .position = {x * w, y * w, 0} }, "transform");
        // scene->AddComponent(entity, renderable{ mesh_handle, material_handle }, "renderable");

        chunk chunk_c {};
        chunk_init(chunk_c);

        scene->m_Registry.AddComponent<chunk>(entity, chunk_c);
        // scene->AddComponent(entity, chunk_c, "chunk");
    }

    app.Run();
}
