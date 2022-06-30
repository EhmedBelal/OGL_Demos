#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

//ogl includes
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cerrno>

std::string GetFileContents(const char* strFilename);

class Shader
{
public:
	//reference ID of the shader program
	GLuint gluiShaderProgramID;

	//constructor to build the shader program
	Shader(const char* cVertexFile, const char* cFragmentFile);

	//shader activation 
	void Activate();

	//shader deletion
	void Delete();
};

#endif
