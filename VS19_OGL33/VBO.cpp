#include "VBO.h"

VBO::VBO(GLfloat* glfVertices, GLsizeiptr glptrSize)
{
	glGenBuffers(1, &gluiID);
	glBindBuffer(GL_ARRAY_BUFFER, gluiID);
	glBufferData(GL_ARRAY_BUFFER, glptrSize, glfVertices, GL_STATIC_DRAW);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER,gluiID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &gluiID);
}