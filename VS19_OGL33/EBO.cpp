#include "EBO.h"

EBO::EBO(GLuint* gluiIndices, GLsizeiptr ptrSize)
{
	glGenBuffers(1, &gluiID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gluiID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ptrSize, gluiIndices, GL_STATIC_DRAW);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gluiID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &gluiID);
}