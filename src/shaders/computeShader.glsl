#version 430     

struct Particle
{
    vec4 velocity;
    vec4 force;

    float density0;
    float density;
    float pressure;
};

layout (local_size_x = 256) in;

layout(std430, binding = 0) buffer positionblock 
{
    vec4 p_positions[];
};

layout(std430, binding = 1) buffer fluidblock 
{ 
    Particle FluidParticles[]; 
};

layout (location = 0) uniform float dt;

void compute_velocity(inout vec4 velocity, vec3 acceleration, float dt)
{
    velocity.xyz += acceleration * dt;
}

void compute_position(inout vec4 position, vec4 velocity, float dt)
{
    position.xyz += velocity.xyz * dt;
}
void main()
{
    int N     = int(gl_NumWorkGroups.x*gl_WorkGroupSize.x);
    int index = int(gl_GlobalInvocationID);

    vec3 gravity = vec3(0.0, 0.0, -9.8);

    compute_velocity(FluidParticles[index].velocity, gravity, dt);
    compute_position(p_positions[index], FluidParticles[index].velocity, dt);
}