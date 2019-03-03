#include "utils.h"
#include "../physics/sphere.h"

GLFWwindow *window;

bool start()
{
    // glfw
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return false;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(WINDOW_W , WINDOW_H, "Ghost SPH", 0, 0);

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

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwPollEvents();
    glfwSetCursorPos(window, WINDOW_W/2, WINDOW_H/2);

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

    //glDisable(GL_CULL_FACE);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    //glDepthFunc(GL_LESS); 

    // Enable blending
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
    //glewExperimental = GL_TRUE;

    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *version  = glGetString( GL_VERSION );

    printf( "Renderer: %s\n", renderer );
    printf( "OpenGL version %s\n\n", version );
    
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

bool check_shader_errors(GLuint shaderID)
{
    GLint result = GL_FALSE;
    int InfoLogLength;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> VertexShaderErrorMessage(InfoLogLength);
        glGetShaderInfoLog(shaderID, InfoLogLength, &InfoLogLength, &VertexShaderErrorMessage[0]);
        printf("Error: Compiler log:\n%s\n", &VertexShaderErrorMessage[0]);
        return false;
    }
    return true;
}

bool check_program_errors(GLuint program)
{
    GLint result = GL_FALSE;
    int InfoLogLength;
    
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> ProgramErrorMessage(InfoLogLength);
        glGetProgramInfoLog(program, InfoLogLength, &InfoLogLength, &ProgramErrorMessage[0]);
        std::cerr << &ProgramErrorMessage[0] << std::endl;
    }
}

GLuint create_vao() {
    std::vector<glm::vec4>  positionData(num_fluid_p);
    std::vector<glm::vec4>  velocityData(num_fluid_p);
    std::vector<glm::vec4>  forceData(num_fluid_p);
    std::vector<float>      densityData(num_fluid_p);
    std::vector<float>      pressureData(num_fluid_p);

    initializer(positionData, velocityData, forceData, densityData, pressureData, num_fluid_p);   

    GLuint vao;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint particles_vbo;
    glGenBuffers(1, &particles_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, particles_vbo);
    glBufferData(GL_ARRAY_BUFFER, num_fluid_p * sizeof(glm::vec4), &positionData[0], GL_STATIC_DRAW);

    GLuint velocities_vbo;
    glGenBuffers(1, &velocities_vbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, velocities_vbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, num_fluid_p * sizeof(glm::vec4), &velocityData[0], GL_STATIC_DRAW);

    
    

    glEnableVertexAttribArray(0);

    GLintptr stride = 4 * sizeof(GLfloat);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, (char*)0 + 0*sizeof(GLfloat));

    const GLuint ssbos[] = {particles_vbo, velocities_vbo};
    glBindBuffersBase(GL_SHADER_STORAGE_BUFFER, 0, 2, ssbos);
    //glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particles_vbo);
    //glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, fluid_ssbo);

    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    return vao;
}