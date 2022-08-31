#include "VAO.h"

VAO::VAO()
{ 
	glGenVertexArrays(1, &ID);
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}

void VAO::LinkAttribute(VBO& VBO, GLuint gluiLayout, GLuint gluiNumComponents, GLenum type, GLsizeiptr ptrStride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(gluiLayout, gluiNumComponents, type, GL_FALSE, ptrStride, offset);
	glEnableVertexAttribArray(gluiLayout);
	VBO.Unbind();
}
