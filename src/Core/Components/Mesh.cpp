#include "Mesh.h"

Mesh::Mesh(GameObject* obj) : Component(obj)
{
	m_VertexArray = std::make_shared<VertexArray>();
}

void Mesh::Clear()
{
	Vertices.clear();
	Indices.clear();
}

void Mesh::ClearBuffers()
{
	if (!m_VertexArray)
	{
		std::cerr << "Error: m_VertexArray is not initalized.\n";
		return;
	}

	Vertices.clear();
	Indices.clear();

	m_VertexArray->UploadBufferData(Vertices, Indices);
}

void Mesh::UploadData()
{
	if (!m_VertexArray)
	{
		std::cerr << "Error: m_VertexArray is not initalized.\n";
		return;
	}

	m_VertexArray->UploadBufferData(Vertices, Indices);
}
