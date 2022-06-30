#include "ShaderClass.h"

std::string	GetFileContents(const char* cFilename)
{
	std::ifstream inFileStream(cFilename, std::ios::binary);
	if(inFileStream)
	{
		std::string strContent;
		inFileStream.seekg(0, std::ios::end);//In the C++ programming language, seekg is a function in the fstream library that allows you to seek to an arbitrary position in a file
		strContent.resize(inFileStream.tellg());//resize the string var to accomodate the input file
		inFileStream.seekg(0,std::ios::beg);
		inFileStream.read(&strContent[0], strContent.size());
		inFileStream.close();
		return(strContent);
	}
	throw(errno);
}

Shader::Shader(const char* szVertexFile, const char* szFragmentFile)
{
	//load the shader code
	std::string strVertexCode = GetFileContents(szVertexFile);
	std::string strFragmentCode = GetFileContents(szFragmentFile);

	const char* szVertexSrc = strVertexCode.c_str();
	const char* szFragmentSrc = strFragmentCode.c_str();

	//COMPILE THE SHADERS
	GLuint gluiVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(gluiVertexShader, 1, &szVertexSrc, NULL);
	glCompileShader(gluiVertexShader);

	GLuint gluiFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(gluiFragmentShader, 1, &szFragmentSrc, NULL);
	glCompileShader(gluiFragmentShader);

	//create a shader program and attach the shaders to it
	gluiShaderProgramID = glCreateProgram();
	glAttachShader(gluiShaderProgramID, gluiVertexShader);
	glAttachShader(gluiShaderProgramID, gluiFragmentShader);
	
	//link the shader program
	glLinkProgram(gluiShaderProgramID);

	//delete the shaders
	glDeleteShader(gluiVertexShader);
	glDeleteShader(gluiFragmentShader);
}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(gluiShaderProgramID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(gluiShaderProgramID);
}
