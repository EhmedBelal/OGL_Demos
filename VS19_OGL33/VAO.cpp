#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &gluiID);
}

void VAO::LinkVBO(VBO& VBO, GLuint gluiLayout)
{
	VBO.Bind();
	glVertexAttribPointer(gluiLayout, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(gluiLayout);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	VBO.Bind();
}

void VAO::Bind()
{
	glBindVertexArray(gluiID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &gluiID);
}