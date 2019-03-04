#ifndef __UTILS__
#define __UTILS__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../physics/sphere.h"

#define WINDOW_W 640
#define WINDOW_H 480

//const int num_fluid_p = 59 * 1024;
const int num_fluid_p = 10*1024;

bool start();
void stop();

std::string check_read_shader(const char* shader_file_path);
bool check_shader_errors(GLuint shader);
bool check_program_errors(GLuint program);

GLuint create_ssbos(int ghost_angle_res, const int ghost_size);
GLuint create_program();

extern GLFWwindow *window;

#endif