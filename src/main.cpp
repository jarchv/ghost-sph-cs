/*
* Ghost SPH on Compute Shader
* Jose Chavez <jose.chavez.alvarez@ucsp.edu.pe>
* xx March 2019
*/

#include "tools/utils.h"
#include "commons/loadshader.h"
#include "commons/controls.h"

int main() {
	start(); //starts a 4.3 GL context+window

	GLuint vao  			= create_vao();
	GLuint shader_program	= create_program(	"../src/shaders/vertexShader.glsl", 
												"../src/shaders/geometryShader.glsl",
											 	"../src/shaders/fragmentShader.glsl");
	if(!shader_program)
		glfwTerminate();

	GLuint acceleration_program  = create_accelerator("../src/shaders/computeShader.glsl");
	if(!acceleration_program)
		glfwTerminate();
	
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	
	float dt = 1.0f/60.0f;

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

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);



    GLuint query;
    glGenQueries(1, &query);
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glBeginQuery(GL_TIME_ELAPSED, query);
		glUseProgram(acceleration_program);
		//glUniform1f(0,deltaTime);
		glDispatchCompute(num_fluid_p/256, 1, 1);
		glEndQuery(GL_TIME_ELAPSED);
		//glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		// normal drawing pass
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_program);

		//MVP matrix
		computeMatricesFromInputs();
		
		glm::mat4 ProjectionMatrix  	= getProjectionMatrix();
		glm::mat4 ViewMatrix 			= getViewMatrix();

		glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
		glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

		glBindVertexArray(vao);
		glDrawArrays(GL_POINTS, 0, num_fluid_p/3);

		if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, 1);
		}
		glfwSwapBuffers(window);

        {
            GLuint64 result;
            glGetQueryObjectui64v(query, GL_QUERY_RESULT, &result);
            //std::cout << result*1.e-6 << " ms/frame" << std::endl;
        }
	}

	glDeleteProgram(shader_program);
	glDeleteProgram(acceleration_program);

	glDeleteVertexArrays(1, &vao);
	stop();

	return 0;
}