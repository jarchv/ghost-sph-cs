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

#define PI 3.14159

void set_positions(std::vector<glm::vec4>& positions, int n);
void initializer(Particle System[], std::vector<glm::vec4>& positions, int n);
/*
void SetSphereNormals(  GLfloat* g_spherevertex_buffer_data,
                        GLfloat* g_spherenormal_buffer_data,
                        int angleRes);
*/
void SphereBuffer(  float   radio, 
                    int     angleRes,
                    int     nSphVtx,
                    std::vector<float> sphereColor,
                    GLfloat* g_spherevertex_buffer_data,
                    GLfloat* g_spherecolor_buffer_data,
                    std::vector<float> sphereCenter);

void SetSphereNormals(  GLfloat* g_spherevertex_buffer_data,
                        GLfloat* g_spherenormal_buffer_data,
                        int angleRes);
#endif

