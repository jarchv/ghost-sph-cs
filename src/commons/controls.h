//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <GLFW/glfw3.h>
#include <stdio.h>

#include "../tools/utils.h"

extern GLFWwindow* window;

glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void computeMatricesFromInputs();