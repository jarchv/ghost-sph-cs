/*
* Ghost SPH on Compute Shaders
* Jose Chavez <jose.chavez.alvarez@ucsp.edu.pe>
* xx March 2019
*/

#include "tools/utils.h"
#include "commons/loadshader.h"
//#include "commons/controls.h"
//#include "physics/sphere.h"

//const int num_fluid_p = 2;

int main() {
	start(); //starts a 4.3 GL context+window

	GLuint vao  			= create_quad_vao();
	GLuint shader_program	= create_program(	"../src/shaders/vertexShader.glsl", 
												"../src/shaders/geometryShader.glsl",
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
	if(!shader_program)
		glfwTerminate();

	GLuint acceleration_program  = create_accelerator("../src/shaders/computeShader.glsl");
	if(!acceleration_program)
		glfwTerminate();
	
	float dt = 1.0f/60.0f;

    glUseProgram(acceleration_program);
    glUniform1f(0, dt);
	//GLuint TimeID = glGetUniformLocation(ray_program, "dt");
	// texture handle and dimensions
	/*
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
	*/
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
		//glDispatchCompute((GLuint)WINDOW_W, (GLuint)WINDOW_H, 1);
		glEndQuery(GL_TIME_ELAPSED);
		//glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		// normal drawing pass
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_program);

		glm::mat4 ProjectionMatrix = glm::perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.f);
		glm::mat4 ViewMatrix       = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -30.0f));
		

		ViewMatrix = glm::rotate(ViewMatrix, 30.0f, glm::vec3(1.0f, 0.0f, 0.0f));

		//glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(View));
		//glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(Projection));

		//MVP matrix
		//computeMatricesFromInputs();
		
		//glm::mat4 ProjectionMatrix  	= getProjectionMatrix();
		//glm::mat4 ViewMatrix 			= getViewMatrix();
		//MVP 				= ProjectionMatrix * ViewMatrix * ModelMatrix;
		
		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
		glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

		glBindVertexArray(vao);
		glDrawArrays(GL_POINTS, 0, num_fluid_p);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, tex_output);
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
		

		if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, 1);
		}
		glfwSwapBuffers(window);

        {
            GLuint64 result;
            glGetQueryObjectui64v(query, GL_QUERY_RESULT, &result);
            std::cout << result*1.e-6 << " ms/frame" << std::endl;
        }
        std::cout << "->" << std::endl;
	}

	stop();
	return 0;
}