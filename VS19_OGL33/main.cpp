#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#pragma region MESH SETUP
//vertex position
GLfloat arrGlfVertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

//indices
GLuint arrGluiIndices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};
#pragma endregion

int main(void)
{
#pragma region OGL SETUP
	//initialize GL and set the version and profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//window instance to hold the GL viewport
	GLFWwindow* glWnd = glfwCreateWindow(800, 800, "GL Window", NULL, NULL);
	if (!glWnd)
	{
		std::cout << "FAILURE: Failed to create OpenGL window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(glWnd);

	//load GLAD so it can configure OpenGL
	gladLoadGL();
	glViewport(0, 0, 600, 600);
#pragma endregion

#pragma region SHADER SETUP
	//shader setup
	Shader objShaderProgram("default.vert", "default.frag");
#pragma endregion

#pragma region VERTEX ARRAY AND BUFFER SETUP
	//generate vertex array object
	VAO objVAO;
	objVAO.Bind();

	//generate vertex buffer link it to vertex position data and activate(bind) it
	VBO objVBO(arrGlfVertices, sizeof(arrGlfVertices));

	//generate element bufer for indices, link it to indices and activate(bind) it
	EBO objEBO(arrGluiIndices,sizeof(arrGluiIndices));
	
	//link VBO to VAO, and assign vertex attribute 0 as vertex position data(3 comps per vertex)
	objVAO.LinkVBO(objVBO, 0);

	//unbind VAO and buffers
	objVAO.Unbind();
	objVBO.Unbind();
	objEBO.Unbind();
#pragma endregion

#pragma region GAME LOOP
	//Game Loop -Process input and render frames
	while(!glfwWindowShouldClose(glWnd))
	{
		//specify the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//set the color
		glClear(GL_COLOR_BUFFER_BIT);
		//tell GL which shader program we want to use
		objShaderProgram.Activate();
		//bind the VAO so the GL can use it to draw data
		objVAO.Bind();
		//draw primitives, number of indices, indices datatype, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//swap the buffers
		glfwSwapBuffers(glWnd);
		//poll window events
		glfwPollEvents();
	}
#pragma endregion

#pragma region DELETE ALL THE OBJECTS
	objVAO.Delete();
	objVBO.Delete();
	objEBO.Delete();
	objShaderProgram.Delete();
	glfwDestroyWindow(glWnd);
	glfwTerminate();
#pragma endregion
	return 0;
}
