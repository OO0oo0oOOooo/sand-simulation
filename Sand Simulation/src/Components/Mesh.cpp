#include "Mesh.h"

Mesh::Mesh(GameObject* obj) : Component(obj) {}

void Mesh::Clear()
{
	Vertices.clear();
	Indices.clear();
}

void Mesh::ClearBuffers()
{
	Vertices.clear();
	Indices.clear();

	m_VertexArray.UploadBufferData(Vertices, Indices);
}

void Mesh::UploadData()
{
	m_VertexArray.UploadBufferData(Vertices, Indices);
}

//Todo: Not Tested
void Mesh::UploadSubData(int offsetV, int offsetI)
{
	m_VertexArray.UploadBufferSubData(Vertices, Indices, offsetV, offsetI);
}

/*
Mesh::Mesh()
{ 
	SetupOpenGLBuffers();
}

Mesh::~Mesh()
{
	delete vao;
	delete vb;
	delete ib;
}

void Mesh::Bind()
{
	glBindVertexArray(*vao);
	ib->Bind();
}

void Mesh::Unbind()
{
	glBindVertexArray(0);
	ib->Unbind();
}


void Mesh::Draw()
{
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Mesh::DrawLine()
{
	glDrawElements(GL_LINES, Indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Mesh::Clear()
{
    Indices.clear();
    Vertices.clear();
}

void Mesh::ClearBuffers()
{
    Indices.clear();
    Vertices.clear();

    ib->UpdateData(Indices);
    vb->UpdateData(Vertices);
}

void Mesh::UploadIBOData()
{
    ib->UpdateData(Indices);
}

void Mesh::UploadVBOData()
{
    vb->UpdateData(Vertices);
}

void Mesh::UploadVBOSubData(const void* data, unsigned int size, unsigned int offset)
{
    vb->UpdateSubData(data, size, offset);
}

void Mesh::SetupOpenGLBuffers()
{
	vao = new unsigned int;
	vb = new VertexBuffer(Vertices);
	ib = new IndexBuffer(Indices);

	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0); // (const void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12); // (const void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
}
*/


