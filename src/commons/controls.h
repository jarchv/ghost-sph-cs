#ifndef __CONTROLS__
#define __CONTROLS__

#define PI 3.14159
#include "../tools/utils.h"

extern GLFWwindow* window;

glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void computeMatricesFromInputs();

#endif