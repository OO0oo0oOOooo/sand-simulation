#include "GameObject.h"

GameObject::GameObject() 
{
    //Todo: Add transform as components then cache maybe
}

void GameObject::AddComponent(Component* component)
{
    m_Components.push_back(component);
}

void GameObject::RemoveComponent(Component* component)
{
    m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), component), m_Components.end());
}

void GameObject::Start()
{
    for (Component* component : m_Components)
    {
        component->Start();
    }
}

void GameObject::Update()
{
    for (Component* component : m_Components)
    {
        component->Update();
    }
}