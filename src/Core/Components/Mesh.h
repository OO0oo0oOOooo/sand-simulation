#pragma once

#include "../GameObject.h"
#include "../../Rendering/VertexArray.h"
#include "../../Rendering/Vertex.h"

#include <memory>
#include <vector>

class Mesh : public Component
{
public:
    Mesh(GameObject* obj);

    void Clear();
    void ClearBuffers();

    void UploadData();

    std::shared_ptr<VertexArray> GetVertexArray() const { return m_VertexArray; }

public:
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

private:
    std::shared_ptr<VertexArray> m_VertexArray;
};
