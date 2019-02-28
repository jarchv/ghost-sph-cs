/*
* Ghost SPH on Compute Shaders
* Jose Chavez <jose.chavez.alvarez@ucsp.edu.pe>
* xx March 2019
*/

#include "tools/utils.h"
#include "commons/loadshader.h"

int main() {
	start(); //starts a 4.3 GL context+window

	if(!create_program("../src/shaders/vertexShader.glsl", "../src/shaders/fragmentShader.glsl"));
		glfwTerminate();

	stop();
	return 0;
}