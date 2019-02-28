#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define WINDOW_W 720
#define WINDOW_H 480

bool start();
void stop();

std::string check_read_shader(const char* shader_file_path);
bool check_shader_errors(GLuint shader);
bool check_program_errors(GLuint program);

GLuint create_vao();
GLuint create_program();

GLuint create_quad_vao();

extern GLFWwindow *window;