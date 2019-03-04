#include "../tools/utils.h"

#ifndef __SOLID__
#define __SOLID__

void build_ghost_particles(	std::vector<glm::vec4>& ghost_pos, 
							std::vector<glm::vec4>& ghost_nom,
							int angle_res,
							float radius,
							glm::vec3 objcenter);

#endif