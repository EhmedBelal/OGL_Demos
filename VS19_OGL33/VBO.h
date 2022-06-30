#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
public:
	//vertex buffer ref
	GLuint gluiID;

	//constructor that generates a vertex buffer and links it to vertices
	VBO(GLfloat* glfVertices, GLsizeiptr glptrSize);

	//bind the vbo
	void Bind();

	//unbind the vbo
	void Unbind();
	
	//delete the vbo
	void Delete();
};
#endif // !VBO_CLASS_H

