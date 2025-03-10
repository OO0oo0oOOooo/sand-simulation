#include "Scene.h"
#include "../Game/World.h"

Scene::Scene(Renderer* renderer) : m_Renderer(renderer)
{
	std::shared_ptr<GameObject> gameObjectWorld = std::make_shared<GameObject>();

	gameObjectWorld->AddComponent<Transform>();
	gameObjectWorld->AddComponent<Mesh>();
	gameObjectWorld->AddComponent<Material>();
	gameObjectWorld->AddComponent<World>();

	AddGameObject(gameObjectWorld);
}

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject)
{
	m_GameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(std::shared_ptr<GameObject> gameObject)
{
	m_GameObjects.erase(std::remove(m_GameObjects.begin(), m_GameObjects.end(), gameObject), m_GameObjects.end());
}

void Scene::Start()
{
	for (std::shared_ptr<GameObject> gameObject : m_GameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update()
{
	for (std::shared_ptr<GameObject> gameObject : m_GameObjects)
	{
		gameObject->Update();
	}
}

void Scene::SubmitToRenderer()
{
	for (std::shared_ptr<GameObject> gameObject : m_GameObjects)
	{
		std::shared_ptr<Transform> transform = gameObject->GetComponent<Transform>();
		if (transform == nullptr)
			continue;

		std::shared_ptr<Mesh> mesh = gameObject->GetComponent<Mesh>();
		if (mesh == nullptr)
			continue;

		std::shared_ptr<Material> material = gameObject->GetComponent<Material>();
		if (material == nullptr)
			continue;

		m_Renderer->NewBatch(material, mesh->GetVertexArray(), transform); 
	}
}
