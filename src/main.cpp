/*
* Ghost SPH on Compute Shaders
* Jose Chavez <jose.chavez.alvarez@ucsp.edu.pe>
* xx March 2019
*/

#include "tools/utils.h"
#include "commons/loadshader.h"
#include "commons/controls.h"
#include "physics/sphere.h"

//const int num_fluid_p = 2;

int main() {
	start(); //starts a 4.3 GL context+window

	GLuint quad_vao  	= create_quad_vao();
	GLuint quad_program	= create_program("../src/shaders/vertexShader.glsl", 
										 "../src/shaders/fragmentShader.glsl");

	//glUseProgram(quad_vao);
	//GLuint MatrixID 	 = glGetUniformLocation(quad_vao, "MVP");
	//GLuint ViewMatrixID  = glGetUniformLocation(quad_vao, "V");
	//GLuint ModelMatrixID = glGetUniformLocation(quad_vao, "M");
    
	/*
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
    GLuintptr stride = 3 * sizeof(float);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, NULL);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, positions_vbo);
    */
	if(!quad_program)
		glfwTerminate();

	GLuint ray_program  = create_accelerator("../src/shaders/computeShader.glsl");
	if(!ray_program)
		glfwTerminate();
	
	glUseProgram(ray_program);
	GLuint TimeID = glGetUniformLocation(ray_program, "dt");
	// texture handle and dimensions
	GLuint tex_output;
	glGenTextures(1, &tex_output);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_output);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, WINDOW_W, WINDOW_H, 0, GL_RGBA, GL_FLOAT, NULL);
	glBindImageTexture(0, tex_output, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

	// Determining the Work Group Size
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


	// MVP declaration
	//glm::mat4 ProjectionMatrix;
	//glm::mat4 ViewMatrix;
	//glm::mat4 MVP;

	//glm::mat4 ModelMatrix = glm::mat4(1.0);

	float deltaTime = 0.0;
	while(!glfwWindowShouldClose(window))
	{
		glUseProgram(ray_program);
		glUniform1f(TimeID,deltaTime);
		glDispatchCompute((GLuint)WINDOW_W, (GLuint)WINDOW_H, 1);

		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		// normal drawing pass
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(quad_program);
		//MVP matrix
		//computeMatricesFromInputs();
		
		//ProjectionMatrix  	= getProjectionMatrix();
		//ViewMatrix 			= getViewMatrix();
		//MVP 				= ProjectionMatrix * ViewMatrix * ModelMatrix;
		
		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		//glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
		//glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		glBindVertexArray(quad_vao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_output);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
		glfwPollEvents();

		if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, 1);
		}
		glfwSwapBuffers(window);

		deltaTime-= 0.01;
	}

	stop();
	return 0;
}