#include "controls.h"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix()
{
	return ViewMatrix;
}

glm::mat4 getProjectionMatrix()
{
	return ProjectionMatrix;
}

// Initial position : +Z
glm::vec3 position = glm::vec3(0.0, 0.0, 1.0);

// Initial angles : 

float horizontalAngle = 3.14f;
float verticalAngle   = 0.0f;

float initialFov      = 90.0f;

float speed 		  = 3.0f;
float mouseSpeed 	  = 0.001f;

void computeMatricesFromInputs()
{
	static double lastTime = glfwGetTime();

	double currentTime     = glfwGetTime();
	float  deltaTime 	   = float(currentTime - lastTime);

	double xpos, ypos;

	// Direction (static)
	glm::vec3 direction(
		0.0,
		0.0,
		1.0
	);	

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		position += direction * deltaTime * speed;
		printf("> up %.3f, %.3f, %.3f\n",position.x, position.y,position.z);
	}

	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		position -= direction * deltaTime * speed;
		printf("> up %.3f, %.3f, %.3f\n", position.x, position.y,position.z);
	}

	float FoV = initialFov;

	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f/3.0f, 0.1f, 100.f);
	/*
	ViewMatrix  	 = glm::lookAt(
								position,
								position + direction,
								glm::vec3(0.0,0.0,-1.0)
								);
	*/
	ViewMatrix 		 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0,-30.0f));
	lastTime = currentTime;
}	
