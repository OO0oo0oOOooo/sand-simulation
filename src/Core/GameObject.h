#pragma once

// Todo: make gameobjects able to refrence the scene
//#include "Rendering/Scene.h"

#include <vector>
#include <memory>
#include <iostream>

class Component;
class GameObject;

class Component
{
public:
    Component(GameObject* gameObject) : gameObject(gameObject) {};

    virtual void Start() {};
    virtual void Update() {};

protected:
    GameObject* gameObject;
};

class GameObject
{
public:
    GameObject();

    void Start();
    void Update();

    void RemoveComponent(std::shared_ptr<Component> component);

    template <typename T>
    std::shared_ptr<T> AddComponent()
    {
        std::shared_ptr<T> component = std::make_shared<T>(this);
        m_Components.push_back(component);
        return component;
    }

	template <typename T>
	std::shared_ptr<T> GetComponent() const
    {
		for (const auto& component : m_Components)
        {
			if (auto ptr = std::dynamic_pointer_cast<T>(component))
            {
				return ptr;
			}
		}
		std::cout << "Can't find component: " << typeid(T).name() << std::endl;
		return nullptr;
	}

private:
    std::vector<std::shared_ptr<Component>> m_Components;
};