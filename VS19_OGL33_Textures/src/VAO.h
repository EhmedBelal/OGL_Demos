#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include <iostream>
#include "VBO.h"

class VAO
{
public:
	VAO();
	GLuint ID;
	void Bind();
	void Unbind();
	void Delete();
	void LinkAttribute(VBO& VBO, GLuint gluiLayout, GLuint gluiNumComponents, GLenum type, GLsizeiptr ptrStride, void* offset);
private:
};
#endif