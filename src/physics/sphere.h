#ifndef __SPHERE__
#define __SPHERE__

#include "../tools/utils.h"

struct Particle{
    glm::vec4 velocity;
    glm::vec4 force;
    
    float     density0 = 1000.0;
    float     density  = 1000.0;
    float     pressure;
};

#endif

#ifndef __INITIALIZER__
#define __INITIALIZER__

void set_positions(std::vector<glm::vec4>& positions, int n);
void initializer(Particle System[], std::vector<glm::vec4>& positions, int n);

#endif

