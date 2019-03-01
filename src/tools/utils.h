#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../physics/sphere.h"

#define WINDOW_W 512
#define WINDOW_H 512

const int num_fluid_p = 2;

bool start();
void stop();
void deleteVBO(int vboName);

std::string check_read_shader(const char* shader_file_path);
bool check_shader_errors(GLuint shader);
bool check_program_errors(GLuint program);

GLuint create_vao();
GLuint create_program();

GLuint create_quad_vao();

extern GLFWwindow *window;