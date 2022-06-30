#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO
{
public:
	GLuint gluiID;
	EBO(GLuint* gluiIndices, GLsizeiptr ptrSize);
	void Bind();
	void Unbind();
	void Delete();
};

#endif // !EBO_CLASS_H

