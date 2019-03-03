#version 430     

struct Particle
{
    vec4 v;
    vec4 f;

    float dty0;
    float dty;
    float press;
};

void compute_velocity(inout vec4 velocity, vec3 acceleration, float dt)
{
    velocity = vec4(velocity.xyz + acceleration * dt, 0.0);
}

void compute_position(inout vec4 position, vec4 velocity, float dt)
{
    position = vec4(position.xyz + velocity.xyz *dt, 1.0);
}

void initialize(inout vec4 position)
{
    position = vec4(0.0,0.0,0.0,1.0);
}
layout (local_size_x = 256) in;

layout(std430, binding = 0) buffer pblock 
{
    vec4 p_position[];
};

layout(std430, binding = 1) buffer vblock 
{ 
    vec4 p_velocity[]; 
};

layout (location = 0) uniform float dt;
layout (location = 1) uniform float num_p;
layout (location = 2) uniform int   nframe;

void main()
{

    int N        = int(gl_NumWorkGroups.x*gl_WorkGroupSize.x);
    int index    = int(gl_GlobalInvocationID);
    vec3 gravity = vec3(0.0, -0.0098, 0.0);

    compute_velocity(p_velocity[index], gravity, dt);
    compute_position(p_position[index],p_velocity[index], dt);
    
}