#include "Scene.h"
#include "../Game/World.h"

Scene::Scene(Renderer* renderer) : m_Renderer(renderer)
{
	GameObject* gameObjectWorld = new GameObject();
	World* world = new World(gameObjectWorld);

	gameObjectWorld->AddComponent(world);
	AddGameObject(gameObjectWorld);
}

void Scene::AddGameObject(GameObject* gameObject)
{
	m_GameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	m_GameObjects.erase(std::remove(m_GameObjects.begin(), m_GameObjects.end(), gameObject), m_GameObjects.end());
}

void Scene::Start()
{
	for (GameObject* gameObject : m_GameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update()
{
	for (GameObject* gameObject : m_GameObjects)
	{
		gameObject->Update();
	}
}

void Scene::SubmitToRenderer()
{
	for (GameObject* gameObject : m_GameObjects)
	{
		Mesh* mesh = gameObject->GetComponent<Mesh>();
		if (mesh == nullptr)
			continue;

		Material* material = gameObject->GetComponent<Material>();
		if (material == nullptr)
			continue;

		m_Renderer->NewBatch(material, &mesh->m_VertexArray, &gameObject->transform);
	}
}
