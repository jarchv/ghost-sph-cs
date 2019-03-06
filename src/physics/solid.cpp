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

    float PI_   = 3.14159;
	//float dphi   = 2 * PI_ / ((float)angle_res);
	float dtheta =     PI_ / ((float)angle_res);

	float dphi;
	float phi;
	float theta;

	for (int j = 0; j < angle_res; j++) 
	{
		theta = dtheta*j;
		float phi_dom = 1.0 + (float(angle_res) - 1.0)*(1.0 - abs(PI_/2 - theta)*2/PI_);

		dphi = 2.0 * PI_ / phi_dom;
		for (int i = 0; i < int(phi_dom); i++)
		{

			phi   = dphi*i;
			

			posY = cos(PI_ - theta)*radius          + objcenter.y;
			posZ = sin(PI_ - theta)*sin(phi)*radius + objcenter.z;
			posX = sin(PI_ - theta)*cos(phi)*radius + objcenter.x;

			/*
            ghost_pos[i*angle_res + j] = glm::vec4(posX, posY, posZ, 0.0);
            ghost_nom[i*angle_res + j] = glm::vec4(	sin(PI_ - theta)*cos(phi), 
                                                	cos(PI_ - theta), 
                                                	sin(PI_ - theta)*sin(phi),
                                                	0.0);  
            */
            ghost_pos.push_back(glm::vec4(posX, posY, posZ, 0.0));
            ghost_nom.push_back(glm::vec4(	sin(PI_ - theta)*cos(phi), 
                                                	cos(PI_ - theta), 
                                                	sin(PI_ - theta)*sin(phi),
                                                	0.0));  
        }
    }
}