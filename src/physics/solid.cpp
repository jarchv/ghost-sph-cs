#include "solid.h"

void build_ghost_particles(	std::vector<glm::vec4>& ghost_pos, 
							std::vector<glm::vec4>& ghost_nom,
							int angle_res,
							float radius,
							glm::vec3 objcenter)
{

    float posX;
    float posY;
    float posZ;

    float PI_ = 3.14159;
	float phi   = 2 * PI_ / ((float)angle_res);
	float theta =     PI_ / ((float)angle_res);
    float dr    = radius  / ((float)angle_res);
    int px, py, pz;
    
	for (int i = 0; i < angle_res; i++)
	{
		for (int j = 0; j < angle_res; j++) 
		{
			posY = cos(PI_ - (theta*j))*radius            + objcenter.y;
			posZ = sin(PI_ - (theta*j))*sin(phi*i)*radius + objcenter.z;
			posX = sin(PI_ - (theta*j))*cos(phi*i)*radius + objcenter.x;

            ghost_pos[i*angle_res + j] = glm::vec4(posX, posY, posZ, 0.0);
            ghost_nom[i*angle_res + j] = glm::vec4(	sin(PI_ - (theta*j))*cos(phi*i), 
                                                	cos(PI_ - (theta*j)), 
                                                	sin(PI_ - (theta*j))*sin(phi*i),
                                                	0.0);  
        }
    }
}