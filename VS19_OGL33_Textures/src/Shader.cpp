#include "Shader.h"

std::string GetFileContent(const char* filename)
{
	std::ifstream inFile(filename, std::ios::binary);
	if(inFile)
	{
		std::string content;
		inFile.seekg(0, std::ios::end);
		content.resize(inFile.tellg());
		inFile.seekg(0, std::ios::beg);
		inFile.read(&content[0], content.size());
		inFile.close();
		return(content);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = GetFileContent(vertexFile);
	std::string fragmentCode = GetFileContent(fragmentFile);

	const char* srcVertex = vertexCode.c_str();
	const char* srcFragment = fragmentCode.c_str();

	GLuint shaderVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shaderVertex, 1, &srcVertex, NULL);
	glCompileShader(shaderVertex);
	CompilationErrorCheck(shaderVertex, "VERTEX");

	GLuint shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderFragment, 1, &srcFragment, NULL);
	glCompileShader(shaderFragment);
	CompilationErrorCheck(shaderFragment, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, shaderVertex);
	glAttachShader(ID, shaderFragment);
	glLinkProgram(ID);
	CompilationErrorCheck(ID, "PROGRAM");

	glDeleteShader(shaderVertex);
	glDeleteShader(shaderFragment);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::CompilationErrorCheck(GLuint gluiShader, const char* type)
{
	GLint isSuccess;
	char infoLog[1024];
	if(type != "PROGRAM")
	{
		glGetShaderiv(gluiShader, GL_COMPILE_STATUS, &isSuccess);
		if(isSuccess == GL_FALSE)
		{
			glGetShaderInfoLog(gluiShader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR::TYPE:" << type<<"\n" << "INFO_LOG:" << infoLog << "\n";
		}
	}else
	{
		glGetProgramiv(gluiShader, GL_LINK_STATUS, &isSuccess);
		if(isSuccess == GL_FALSE)
		{
			glGetProgramInfoLog(gluiShader, 1024, NULL, infoLog);
			std::cout << "PROGRAM_LINK_ERROR::TYPE:" << type << "\n" << "INFO_LOG:" << infoLog << "\n";
		}
	}
}

