#ifndef VBO_H
#define VBO_H

//#include <glad/glad.h>

class VBO
{
public:
	VBO(GLfloat* glfVertices, GLsizeiptr ptrSize);
	GLuint ID;
	void Bind();
	void Unbind();
	void Delete();
};
#endif

