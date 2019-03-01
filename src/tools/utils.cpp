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

GLuint create_quad_vao() {
	GLuint vao = 0, vbo = 0;
    /*
    float verts[] = {  -0.5f, -0.5f, // (x    , y    )
                        0.0f,  0.0f, 
                       -0.5f,  0.5f, // (x    , y + h)
                        0.0f,  1.0f,
						0.5f, -0.5f, // (x + w, y    )
                        1.0f,  0.0f, 
                        0.5f,  0.5f, // (x + w, y + h)
                        1.0f,  1.0f };
    */
    float verts[] = {  -1.0f, -1.0f, // (x    , y    )
                        0.0f,  0.0f, 
                       -1.0f,  1.0f, // (x    , y + h)
                        0.0f,  1.0f,
                        1.0f, -1.0f, // (x + w, y    )
                        1.0f,  0.0f, 
                        1.0f,  1.0f, // (x + w, y + h)
                        1.0f,  1.0f };

	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, 16 * sizeof(float), verts, GL_STATIC_DRAW );
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	glEnableVertexAttribArray( 0 );
	GLintptr stride = 4 * sizeof( float );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, stride, NULL );
	glEnableVertexAttribArray( 1 );
	GLintptr offset = 2 * sizeof( float );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset );

    Particle FluidParticles[num_fluid_p];

    for (int iprt = 0; iprt < num_fluid_p; iprt++)
    {
        FluidParticles[iprt].position = glm::vec3(-5.0 + float(iprt*10.0),0.0,0.0);
    }

    GLuint positions_vbo;
    glGenBuffers(1, &positions_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, positions_vbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, num_fluid_p * sizeof(struct Particle), &FluidParticles[0], GL_STATIC_DRAW);


    glEnableVertexAttribArray(2);
    GLintptr stride2 = 3 * sizeof(float);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, NULL);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, positions_vbo);

    return vao;
}