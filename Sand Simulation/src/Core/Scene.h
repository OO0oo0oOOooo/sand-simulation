#pragma once

#include "GameObject.h"
#include "../Rendering/Renderer.h"

#include <vector>
#include <memory>

class Scene
{
public:
	//Scene() = default;
	Scene(Renderer* renderer);

	void AddGameObject(std::shared_ptr<GameObject> gameObject);
	void RemoveGameObject(std::shared_ptr<GameObject> gameObject);

	void Start();
	void Update();

	void SubmitToRenderer();

private:
	std::vector<std::shared_ptr<GameObject>> m_GameObjects;
	//std::vector<GameObject*> m_GameObjects;

	// Todo: Refactor this out
	Renderer* m_Renderer;

	// Todo: Scene should have a default camera for when there is no gameobject with a camera component in the scene
	// Camera m_MainCamera
};











/*
	Todo: Scene Manager
	- Manages all scenes
	- Creates scenes
	- Deletes scenes
	- Loads scenes
	- Gets active scene

class SceneManager
{
public:
	SceneManager(const SceneManager&) = delete;
	SceneManager() = default;

	void LoadScene(int sceneId) {}

	void CreateScene() { m_Scenes.emplace_back(new Scene(this)); }
	void DeleteScene(int sceneId) { m_Scenes.erase(m_Scenes.begin() + sceneId); }

	static Scene* GetActiveScene() { return m_ActiveScene; }

private:
	Scene* m_ActiveScene;
	std::vector<Scene*> m_Scenes;

	Renderer* m_Renderer = nullptr;
}; 
*/