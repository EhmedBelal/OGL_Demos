#pragma region HEADERS
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "src/Shader.h"
#include "src/VAO.h"
#include "src/VBO.h"
#include "src/EBO.h"
#include "src/Texture.h"
#pragma endregion

#pragma region MACROS
#define MAIN_FAIL 1
#define MAIN_SUCCESS 0
#define FAILURE -1
#define SUCCESS 1
#pragma endregion

#pragma region CONFIG
const unsigned int W_WIDTH = 800;
const unsigned int W_HEIGHT = 800;
const unsigned int V_WIDTH = 800;
const unsigned int V_HEIGHT = 800;
#pragma endregion

#pragma region MESH DATA
GLfloat glfVertices[] =
{
	//     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

GLuint gluiIndices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};
#pragma endregion

#pragma region MAIN
int main()
{
	std::cout << "GL Textures" << std::endl;

#pragma region GL INIT
	if(!glfwInit())
	{
		std::cout << "GLFW::INIT: FAILURE\n";
		return FAILURE;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* glfwWin = glfwCreateWindow(W_WIDTH, W_HEIGHT, "GL Window", NULL, NULL);
	if(glfwWin==NULL)
	{
		std::cout<<"GLFW::WINDOW::CREATE: FAILURE\n";
		glfwTerminate();
		return FAILURE;
	}
	glfwMakeContextCurrent(glfwWin);

	if(!gladLoadGL())
	{
		std::cout << "GLAD::LOAD_GL: FAILURE\n";
		glfwTerminate();
		return FAILURE;
	}
	glViewport(0, 0, V_WIDTH, V_HEIGHT);
#pragma endregion

#pragma region SHADER SETUP
	Shader ShaderProgram(".\\src\\default.vs", ".\\src\\default.fs");
#pragma endregion

#pragma region VAO SETUP
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(glfVertices, sizeof(glfVertices));
	EBO EBO1(gluiIndices, sizeof(gluiIndices));

	VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	VAO1.LinkAttribute(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//GLuint uniID = glGetUniformLocation(ShaderProgram.ID, "scale");
#pragma endregion

#pragma region TEXTURE SETUP
	Texture TexSanic("sanic.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	TexSanic.TexUnit(ShaderProgram, "tex0", 0);
#pragma endregion

#pragma region MAIN LOOP
	while(!glfwWindowShouldClose(glfwWin))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ShaderProgram.Activate();
		TexSanic.Bind();
		//glUniform1f(uniID, 0.5f);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(glfwWin);
		glfwPollEvents();
	}
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	TexSanic.Delete();
	ShaderProgram.Delete();
	glfwDestroyWindow(glfwWin);
	glfwTerminate();
#pragma endregion
	return MAIN_SUCCESS;
}
#pragma endregion