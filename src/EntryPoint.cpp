#include "Engine.h"
#include "SandSimulation.h"

int main() {
    Application app;

    Scene* scene = app.GetScene();
    ResourceManager* rm = ResourceManager::GetResourceManager();

    resource_handle shader_handle = rm->LoadShader("default_shader");
    resource_handle texture_handle = rm->CreateTexture(64 * 6, 64 * 4);
    resource_handle material_handle = rm->CreateMaterial(shader_handle, texture_handle);

    scene->m_Registry.RegisterComponent("transform", sizeof(transform), transform_save, transform_load);
    scene->m_Registry.RegisterComponent("renderable", sizeof(renderable), renderable_save, renderable_load);
    scene->m_Registry.RegisterComponent("world", sizeof(world), world_save, world_load);
    scene->m_Registry.RegisterComponent("chunk", sizeof(chunk), nullptr, nullptr);

    size_t width = 3;
    size_t height = 3;
    size_t area = width * height;
    size_t cw = 64;

    world world_c {
        .width = width,
        .height = height,
        .chunk_width = cw,
    };

    world_c.chunks.resize(area);

    uint32_t entity = scene->CreateEntity();
    scene->AddComponent(entity, transform{}, "transform");
    scene->AddComponent(entity, world_c, "world");

    for (int i = 0; i < area; i++) {
        int x = get_x(i, width);
        int y = get_y(i, width);
        int w = cw * 1;
        int h = cw * 1;

        std::cout << "============" << "\n";
        std::cout << "X: " << x << "\n";
        std::cout << "Y: " << y << "\n";
        std::cout << "w: " << w << "\n";
        std::cout << "h: " << h << "\n";
        std::cout << "============" << "\n";

        Vertex v1{glm::vec3{0, 0, 0}, glm::vec4{0, 0, 1, 1}, glm::vec2{0, 0}};
        Vertex v2{glm::vec3{0, h, 0}, glm::vec4{0, 1, 0, 1}, glm::vec2{0, 1}};
        Vertex v3{glm::vec3{w, 0, 0}, glm::vec4{1, 0, 0, 1}, glm::vec2{1, 0}};
        Vertex v4{glm::vec3{w, h, 0}, glm::vec4{1, 1, 0, 1}, glm::vec2{1, 1}};

        resource_handle mesh_handle = rm->CreateMesh({v1, v2, v3, v4}, {0, 1, 2, 2, 1, 3});

        uint32_t entity = scene->CreateEntity();
        scene->AddComponent(entity, transform{.position = {x * w, y * h, 0}, .matrix_dirty = true,}, "transform");
        scene->AddComponent(entity, renderable{mesh_handle, material_handle}, "renderable");
        scene->AddComponent(entity, chunk{}, "chunk");
    }

    app.Run();
}
