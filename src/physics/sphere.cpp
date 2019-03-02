#include "../tools/utils.h"
#include "sphere.h"

void set_positions(std::vector<glm::vec4>& positions, glm::vec3 parallelepiped, glm::vec3 center, int n)
{
	float epsilon_x;
	float epsilon_y;
	float epsilon_z;

	float alpha = 1.0;

	for (int i = 0; i < n; i++)
	{	
        epsilon_x = ((float)(rand()%1000) / 1000.0);
        epsilon_y = ((float)(rand()%1000) / 1000.0);
        epsilon_z = ((float)(rand()%1000) / 1000.0);

        positions[i].x = epsilon_x * parallelepiped.x - parallelepiped.x/2.0 + center.x;
		positions[i].y = epsilon_y * parallelepiped.y - parallelepiped.y/2.0 + center.y;// 		= glm::gaussRand(glm::vec4(0,0,0,1), glm::vec4(1, 0.2, 1, 0));
		positions[i].z = epsilon_z * parallelepiped.z - parallelepiped.z/2.0 + center.z;
		positions[i].w = alpha;
	}
}

void initializer(Particle System[], std::vector<glm::vec4>& positions, int n)
{
	glm::vec3 parallelepiped 	= glm::vec3(2.0,2.0,6.0);
	glm::vec3 center			= glm::vec3(0.0,0.0,0.0);

	set_positions(positions, parallelepiped, center, n);

	for (int i = 0; i < n; i++)
	{	
		System[i].velocity 	= glm::vec4(0);
		System[i].force     = glm::vec4(0);
		System[i].density0  = 1000.0;
		System[i].density   = 1000.0;
	}
}