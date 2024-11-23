#pragma once

#include "Components/Transform.h"
#include <vector>
#include <iostream>

class Component;
class GameObject;

class Component
{
public:
    Component(GameObject* gameObject) : gameObject(gameObject) {}

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

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

    template <typename T>
    T* GetComponent()
    {
        for (Component* component : m_Components)
        {
            if (T* t = dynamic_cast<T*>(component))
            {
                return t;
            }
        }

        std::cout << "Cant find component" << std::endl;
        return nullptr;
    }

public:
    Transform transform;
    //Material material;

private:
    std::vector<Component*> m_Components;
};