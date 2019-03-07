#include "solid.h"
#include <math.h>

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


	/*
    rnd = 1.
    if randomize:
        rnd = random.random() * samples

    points = []
    offset = 2./samples
    increment = math.pi * (3. - math.sqrt(5.));

    for i in range(samples):
        y = ((i * offset) - 1) + (offset / 2);
        r = math.sqrt(1 - pow(y,2))

        phi = ((i + rnd) % samples) * increment

        x = math.cos(phi) * r
        z = math.sin(phi) * r

        points.append([x,y,z])

    return points
	*/
	float offset    = 2.0/((float)angle_res);
	float increment = PI_ * (3.0 - sqrt(5.0));

	float rtmp;
	//float phi;

	glm::vec3 posXYZ;
	glm::vec3 posXYZ_dir;
	for (int i = 0; i < angle_res; i++)
	{
		posY = ((i * offset) - 1.0) + (offset / 2.0);
		rtmp = sqrt(1.0 - pow(posY,2.0));

		phi = ((i + 1) % angle_res) * increment;

		posX = cos(phi) * rtmp;
		posZ = sin(phi) * rtmp;

		posXYZ = glm::vec3(posX, posY, posZ);

		float l = glm::length(posXYZ);
		posXYZ_dir = posXYZ * (1.0f/l);

		posXYZ += posXYZ_dir * (radius - l);
        ghost_pos.push_back(glm::vec4(	posXYZ + objcenter, 0.0));
        ghost_nom.push_back(glm::vec4(	glm::normalize(posXYZ),0.0));  

	}	
	/*
	for (int j = 0; j < angle_res/2; j++) 
	{
		theta = dtheta*j;

		//float phi_dom = 1.0 + (angle_res - 1.0) * (sin(PI_ - theta));
		//float phi_dom = 4.0 + (float(angle_res) - 4.0)*(1.0 - abs(PI_/2.0 - theta)*2.0/PI_);

		//dphi = 2.0 * PI_ / (float(angle_res));

		float phi_dom = angle_res * sin(theta) + 1.0;

		dphi = 2.0 * PI_ / (float(phi_dom));
		for (int i = 0; i < ceil(phi_dom); i++)
		{

			phi   = dphi*float(i);
			

			posY = cos(PI_ - theta)*radius          + objcenter.y;
			posZ = sin(PI_ - theta)*sin(phi)*radius + objcenter.z;
			posX = sin(PI_ - theta)*cos(phi)*radius + objcenter.x;

            ghost_pos.push_back(glm::vec4(posX, posY, posZ, 0.0));
            ghost_nom.push_back(glm::vec4(	sin(PI_ - theta)*cos(phi), 
                                                	cos(PI_ - theta), 
                                                	sin(PI_ - theta)*sin(phi),
                                                	0.0));  
        }
    }
    */
}