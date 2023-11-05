#include "Mesh.h"

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

void Mesh::SetupOpenGLBuffers()
{
	vao = new unsigned int;
	vb = new VertexBuffer(vertices);
	ib = new IndexBuffer(indices);

	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0); // (const void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12); // (const void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
}