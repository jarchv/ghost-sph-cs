#include <iostream>
#include "loadshader.h"
#include "../tools/utils.h"

GLuint create_program(  const char* vertex_file_path, 
                        const char* geometry_file_path,
                        const char* fragment_file_path)
{
    // Create the shaders
    GLuint VertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    GLuint GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string VertexShaderCode   = check_read_shader(vertex_file_path);   // Read the Vertex Shader Code from the file
    std::string GeometryShaderCode = check_read_shader(geometry_file_path);   // Read the Geometry Shader Code from the file
    std::string FragmentShaderCode = check_read_shader(fragment_file_path); // Read the Fragment Shader code from the file

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    if (!check_shader_errors(VertexShaderID))
        return 0;

    // Compile Geometry Shader
    printf("Compiling shader : %s\n", geometry_file_path);
    char const* GeometrySourcePointer = GeometryShaderCode.c_str();
    glShaderSource(GeometryShaderID, 1, &GeometrySourcePointer, NULL);
    glCompileShader(GeometryShaderID);

    // Check Vertex Shader
    if (!check_shader_errors(GeometryShaderID))
        return 0;

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const* FragmentSourcePointer  = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);
    
     // Check Fragment Shader
    if (!check_shader_errors(FragmentShaderID))
        return 0;

    // Linking the program

    printf("\nLinking program...\n\n");
    GLuint ProgramID = glCreateProgram();

    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, GeometryShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    
    glLinkProgram(ProgramID);

    // Check the program
    if(!check_program_errors(ProgramID));

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}


GLuint create_accelerator(const char* compute_file_path)
{
    // Create the shaders
    GLuint ComputeShaderID   = glCreateShader(GL_COMPUTE_SHADER);

    std::string ComputeShaderCode   = check_read_shader(compute_file_path);   // Read the Compute Shader Code from the file
    // Compile Compute Shader
    printf("Compiling shader : %s\n", compute_file_path);
    char const* ComputeSourcePointer = ComputeShaderCode.c_str();
    glShaderSource(ComputeShaderID, 1, &ComputeSourcePointer, NULL);
    glCompileShader(ComputeShaderID);

    // Check Compute Shader
    if (!check_shader_errors(ComputeShaderID))
        return 0;

    printf("\nLinking program...\n\n");
    GLuint ProgramID = glCreateProgram();

    glAttachShader(ProgramID, ComputeShaderID);    
    glLinkProgram(ProgramID);

    // Check the program
    if(!check_program_errors(ProgramID));

    glDetachShader(ProgramID, ComputeShaderID);
    glDeleteShader(ComputeShaderID);

    return ProgramID;
}
