#include "GameObject.h"

GameObject::GameObject() {}

void GameObject::RemoveComponent(std::shared_ptr<Component> component)
{
    m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), component), m_Components.end());
}

void GameObject::Start()
{
    for (const auto& component : m_Components)
    {
        component->Start();
    }
}

void GameObject::Update()
{
    for (const auto& component : m_Components)
    {
        component->Update();
    }
}