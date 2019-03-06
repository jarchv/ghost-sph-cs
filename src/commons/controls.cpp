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

glm::vec3 position = glm::vec3(0.0, -10.0, -30.0);
//glm::vec3 position = glm::vec3(0.0, 0.0, 5.0);
// Initial angles : 

float initialFov      = 45.0f;

float horizontalAngle = 0.0f;
float verticalAngle   = 0.0f;
float speed 		  = 3.0f;
float mouseSpeed 	  = 0.001f;

void computeMatricesFromInputs()
{
	static double lastTime = glfwGetTime();

	double currentTime     = glfwGetTime();
	float  deltaTime 	   = float(currentTime - lastTime);
	
	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, WINDOW_W/2, WINDOW_H/2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(WINDOW_W/2 - xpos );
	verticalAngle   += mouseSpeed * float(WINDOW_H/2 - ypos );

	// Direction (static)
	
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);	
	
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		position += direction * deltaTime * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		position -= direction * deltaTime * speed;
	}
	
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}
	
	float FoV = initialFov;
	
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f/3.0f, 0.1f, 100.f);

	//ViewMatrix 		 = glm::translate(glm::mat4(1.0f), position);
	//ViewMatrix 		 = glm::rotate(ViewMatrix, 30.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								glm::vec3(0,1,0)//up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	lastTime 		 = currentTime;
}	
