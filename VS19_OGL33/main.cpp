//HEADERS
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


//MACROS
#define MAIN_FAIL -1
#define MAIN_SUCCESS 0
#define FAILURE 0
#define SUCCESS 1

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

GLfloat glfVertexInputData[] =
{
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f  // Lower right corner
};

GLuint gluiIndices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};

int main(void)
{	
#pragma region OPENGL SETUP
	if(glfwInit() == GLFW_FALSE)
	{
		std::cout << "GLFW::INIT: Failure" << std::endl;
		return FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* glfwWindow = glfwCreateWindow(SCR_WIDTH ,SCR_HEIGHT , "GL Window", NULL, NULL);
	if(!glfwWindow)
	{
		std::cout << "GLFW::WINDOW::CREATE: Failure" << std::endl;
		glfwTerminate();
		return FAILURE;
	}
	glfwMakeContextCurrent(glfwWindow);

	if(!gladLoadGL())
	{
		std::cout << "GLAD::LOAD_GL: Failure" << std::endl;
		glfwTerminate();
		return MAIN_FAIL;
	}
	glViewport(0, 0, 800, 800);
#pragma endregion

#pragma region SHADER SETUP
	Shader	objShaderProgram("default.vert", "default.frag");
#pragma endregion

#pragma region VERTEX SETUP
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(glfVertexInputData, sizeof(glfVertexInputData));
	EBO EBO1(gluiIndices, sizeof(gluiIndices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//Texture
	int iImgWidth, iImgHeight, iNumColors;
	unsigned char* bytes = stbi_load("pop_cat.png", &iImgWidth, &iImgHeight, &iNumColors, 0);

	GLuint gluiTexture;
	glGenTextures(1, &gluiTexture);
#pragma endregion

#pragma region GAME LOOP
	while(!glfwWindowShouldClose(glfwWindow))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		objShaderProgram.Activate();

		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();
	}
#pragma endregion

#pragma region DELETE OBJECTS
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &gluiTexture);
	objShaderProgram.Delete();
#pragma endregion

	glfwDestroyWindow(glfwWindow);
	glfwTerminate();
	std::cout << "MAIN::EXIT: Success";
	return SUCCESS;
}
