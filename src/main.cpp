/*
* Ghost SPH on Compute Shader
* Jose Chavez <jose.chavez.alvarez@ucsp.edu.pe>
* xx March 2019
*/

#include "tools/utils.h"
#include "commons/loadshader.h"
#include "commons/controls.h"

int ghost_angle_res    = 2000;
//const int ghost_size = ghost_angle_res * ghost_angle_res;
//const int ghost_size   = ghost_angle_res * ghost_angle_res;

int ghost_size_tmp;

const char* cmd = "ffmpeg -r 20 -f rawvideo -pix_fmt rgba -s 640x480 -i - "
                  "-threads 0 -preset fast -y -pix_fmt yuv420p -crf 21 -vf vflip output.mp4";

FILE* ffmpeg = popen(cmd, "w");

int* buffer = new int[WINDOW_W*WINDOW_H];

int main() {
	start(); //starts a 4.3 GL context+window

	GLuint vao  			= create_ssbos(ghost_angle_res, ghost_size_tmp);

    const int ghost_size = ghost_size_tmp;

    std::cout << "ghost_size : " << ghost_size << std::endl;
	GLuint shader_program	= create_program(	"../src/shaders/particle_vertexShader.glsl", 
												"../src/shaders/particle_geometryShader.glsl",
											 	"../src/shaders/particle_fragmentShader.glsl");
	
	GLuint object_program   = create_obj_program( "../src/shaders/obj_vertexShader.glsl", 
												  "../src/shaders/obj_fragmentShader.glsl" 
												);
	if(!shader_program)
		glfwTerminate();

	GLuint acceleration_program  = create_accelerator("../src/shaders/particle_computeShader.glsl");
	if(!acceleration_program)
		glfwTerminate();
	

	

	float dt = 4.0f/600.0f;

    //float dt = 0.0f;
    glUseProgram(acceleration_program);
    glUniform1f(0, dt);

	int work_grp_cnt[3];

	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_cnt[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_cnt[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_cnt[2]);

	printf("max global (total) work group size x:%i y:%i z:%i\n", 	work_grp_cnt[0], 
																	work_grp_cnt[1], 
																	work_grp_cnt[2]);
	
	int work_grp_size[3];

	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);

	printf("max local (in one shader) work group sizes x:%i y:%i z:%i\n", 	work_grp_size[0], 
																			work_grp_size[1], 
																			work_grp_size[2]);

	int work_grp_inv;
	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_grp_inv);
	printf("max local work group invocations %i\n", work_grp_inv);

	//glDisable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE, GL_ONE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /*
    * Solid Parameters
    * ================
    */

    float obj_radio    = 2.2;
    int   obj_angleres = 100;
    int   nSphVtx      = 18;
    int objectSizeRes  = nSphVtx * obj_angleres * obj_angleres;
    
    std::vector<float> obj_color  = {1.0, 0.3, 0.3};
    std::vector<float> obj_center = {0.0, -0.10, 20.0};
    

    static GLfloat *g_objectvertex_buffer_data = new GLfloat[objectSizeRes];
    static GLfloat *g_objectcolor_buffer_data  = new GLfloat[objectSizeRes];
    static GLfloat *g_objectnormal_buffer_data = new GLfloat[objectSizeRes];

    SphereBuffer(   obj_radio, 
                    obj_angleres,
                    nSphVtx,
                    obj_color,
                    g_objectvertex_buffer_data,
                    g_objectcolor_buffer_data,
                    obj_center);
    
    SetSphereNormals(   g_objectvertex_buffer_data, 
                        g_objectnormal_buffer_data,
                        obj_angleres);

    GLuint objectbuffer;

    glGenBuffers(1, &objectbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,   objectbuffer);
    glBufferData(GL_ARRAY_BUFFER,   objectSizeRes * sizeof(float),
                                    g_objectvertex_buffer_data ,
                                    GL_STATIC_DRAW); 

    GLuint objectcolor_buffer;

    glGenBuffers(1, &objectcolor_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, objectcolor_buffer);
    glBufferData(GL_ARRAY_BUFFER,   objectSizeRes * sizeof(float),
                                    g_objectcolor_buffer_data ,
                                    GL_STATIC_DRAW); 

    GLuint objectnormal_buffer;

    glGenBuffers(1, &objectnormal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, objectnormal_buffer);
    glBufferData(GL_ARRAY_BUFFER, objectSizeRes * sizeof(float),
                                         g_objectnormal_buffer_data ,
                                         GL_STATIC_DRAW); 

    glUseProgram(object_program);
    GLuint TransparentID = glGetUniformLocation(object_program, "Transparent");
    GLuint LightID       = glGetUniformLocation(object_program, "LightPosition_worldspace");
    
        
    GLuint MatrixID      = glGetUniformLocation(object_program, "MVP");
    GLuint ViewMatrixID  = glGetUniformLocation(object_program, "V");
    GLuint ModelMatrixID = glGetUniformLocation(object_program, "M");  

    glm::vec3 lightPos = glm::vec3(-10,35,0);
    glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
    glUniform1f(TransparentID,0.5);

    glUseProgram(shader_program);
    GLuint LightID_p        = glGetUniformLocation(shader_program, "LightPosition_worldspace_p");
    GLuint ModelMatrixID_p  = glGetUniformLocation(shader_program, "M_p");  

    glUniform3f(LightID_p, lightPos.x, lightPos.y, lightPos.z);
    /*
    * Time query:
    * ==========
    */

    double sumTime = 0.0;
    GLuint query;
    glGenQueries(1, &query);

    int nframe = 0;
    int steps_per_frame = 2; 
    float rec_seconds   = 0;
	while(!glfwWindowShouldClose(window))
	{
		glBeginQuery(GL_TIME_ELAPSED, query);
        //glClear(GL_COLOR_BUFFER_BIT);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        nframe++;
       
        computeMatricesFromInputs();
        glm::mat4 ProjectionMatrix  = getProjectionMatrix();
        glm::mat4 ViewMatrix        = getViewMatrix();
        glm::mat4 ModelMatrix       = glm::mat4(1.0);
        glm::mat4 MVP               = ProjectionMatrix * ViewMatrix * ModelMatrix;   
		
        

        
        


        //glDisableVertexAttribArray(0);
        //glDisableVertexAttribArray(1);
        //glDisableVertexAttribArray(2);
        
        glUseProgram(acceleration_program);
        glUniform1f(1,num_fluid_p);
        glUniform1i(2,ghost_size);
        glDispatchCompute(num_fluid_p/512, 1, 1);
        
        //glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        // normal drawing pass
        glUseProgram(shader_program);

        //MVP matrix
        glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
        glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
        glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(ModelMatrix));

        glBindVertexArray(vao);
        glDrawArrays(GL_POINTS, 0, num_fluid_p);

        
        // Send our transformation to the currently bound shader, 
        // in the "MVP" uniform
        glUseProgram(object_program);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

        glEnableVertexAttribArray(4);
        glBindBuffer(GL_ARRAY_BUFFER, objectbuffer);
        glVertexAttribPointer(
            4,          // attibute 2, must match the layout in the shader
            3,          // size
            GL_FLOAT,   // type
            GL_FALSE,   // normalizerd?
            0,          // stride
            (void*)0    // array buffer offset
        );



        // 2th attribute buffer : colors
        glEnableVertexAttribArray(5);
        glBindBuffer(GL_ARRAY_BUFFER, objectcolor_buffer);
        glVertexAttribPointer(
            5,          // attibute 2, must match the layout in the shader
            3,          // size
            GL_FLOAT,   // type
            GL_FALSE,   // normalizerd?
            0,          // stride
            (void*)0    // array buffer offset
        );
        
        // 3th attribute buffer : colors
        glEnableVertexAttribArray(6);
        glBindBuffer(GL_ARRAY_BUFFER, objectnormal_buffer);
        glVertexAttribPointer(
            6,          // attibute 2, must match the layout in the shader
            3,          // size
            GL_FLOAT,   // type
            GL_FALSE,   // normalizerd?
            0,          // stride
            (void*)0    // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, objectSizeRes/3);
        
		if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, 1);
		}

        glfwPollEvents();
		glfwSwapBuffers(window);

        if (nframe %(steps_per_frame) == 0)
        {
            glReadPixels(0, 0, WINDOW_W, WINDOW_H, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
            fwrite(buffer, sizeof(int)*WINDOW_W*WINDOW_H, 1, ffmpeg);
        }

        glEndQuery(GL_TIME_ELAPSED);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        {
            GLuint64 result;
            glGetQueryObjectui64v(query, GL_QUERY_RESULT, &result);

            sumTime += result * 1e-6;
            double avgTime = sumTime/((double)nframe);
            std::cout << result*1.e-6 << " ms/frame" << ", avgTime = "<< avgTime << " ms";
            rec_seconds = (float)nframe / (20.0 * (float)steps_per_frame);
            std::cout << ", recording = "<< rec_seconds << " s"<<std::endl;
        }
	}
    pclose(ffmpeg);
	glDeleteProgram(shader_program);
	glDeleteProgram(acceleration_program);
	glDeleteProgram(object_program);

	glDeleteVertexArrays(1, &vao);
	stop();

	return 0;
}