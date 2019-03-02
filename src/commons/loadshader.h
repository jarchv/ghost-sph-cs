//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include "../tools/utils.h"

GLuint create_program(  const char* vertex_file_path, 
                        const char* geometry_file_path,
                        const char* fragment_file_path);

GLuint create_accelerator(const char* compute_file_path);