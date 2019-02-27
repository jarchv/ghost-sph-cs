#include "utils.h"

GLFWwindow *window;

bool start()
{
    // glfw
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_W , WINDOW_H, "Ghost SPH", NULL, NULL);

    if (!window)
    {
        fprintf(stderr, "ERROR: coutd not start window with GLFW3\n");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    // glew
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "ERROR: failed to initialize GLEW\n");
        glfwTerminate();
        return false;
    } 

    glewExperimental = GL_TRUE;

    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *version  = glGetString( GL_VERSION );

    printf( "Renderer: %s\n", renderer );
    printf( "OpenGL version %s\n", version );
    
    return true;
}

void stop() { 
    glfwTerminate(); 
}

std::string check_read_shader(const char* shader_file_path)
{
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(shader_file_path, std::ios::in);
    
    if (VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    } 
    else
    {
        printf("Imposible to open %s\n", shader_file_path);
        getchar();
        return 0;
    }

    return VertexShaderCode;
}