#version 430     

struct Particle
{
    vec4 v;
    vec4 f;

    float dty0;
    float dty;
    float press;
};

layout (local_size_x = 32) in;

layout(std430, binding = 0) buffer pblock 
{
    vec4 p_position[];
};

layout(std430, binding = 1) buffer vblock 
{ 
    vec4 p_velocity[]; 
};

layout(std430, binding = 2) buffer fblock 
{
    vec4 p_force[];
};

layout(std430, binding = 3) buffer dblock 
{ 
    float p_density[]; 
};

layout(std430, binding = 4) buffer pressblock 
{
    float p_pressure[];
};

layout(std430, binding = 5) buffer ghost_pblock
{
    vec4 ghost_p_position[];
};

layout(std430, binding = 6) buffer ghost_nblock
{
    vec4 ghost_p_normal[];
};

layout (location = 0) uniform float dt;
layout (location = 1) uniform float num_p;
layout (location = 2) uniform int   ghost_size;

void compute_velocity(inout vec4 velocity, vec3 force, float invMASS, float dt)
{
    velocity = vec4(velocity.xyz + (force * dt) * invMASS, 0.0);
}

void compute_position(inout vec4 position, vec4 velocity, float dt)
{
    position = vec4(position.xyz + velocity.xyz *dt, 1.0);
}

float densityKernel(float delta, float h, float h_9)
{
    float factor = (h * h  - delta * delta);
    factor = factor * factor * factor;

    return factor * 365.0 /(64.0 * h_9 * 3.14159);
}

vec3 KernelGrad(vec3 deltav, float h, float h_6)
{
    float r = sqrt(dot(deltav,deltav));

    if (r == 0)
        return vec3(0.0,0.0,0.0);

    float factor = (45.0 / (3.14159 * h_6)) * (h - r) * (h - r);
    
    return  - factor * normalize(deltav); 
}

float KernelLaplacian(vec3 delta, float h, float h_6)
{
    float r = length(delta);
    if (r == 0)
        return 0.0;

    float res = (45.0 / (3.14159 * h_6)) * (h - r) ;

    return res;
}
void compute_density(float delta, float MASS, float h, float h_9, inout float density)
{
    density += MASS * densityKernel(delta, h, h_9);
}

shared vec4  tmp[gl_WorkGroupSize.x];
shared vec4  vel[gl_WorkGroupSize.x];
shared float den[gl_WorkGroupSize.x];
shared float press[gl_WorkGroupSize.x];
shared vec4 normal[gl_WorkGroupSize.x];
void main()
{
    float particle_radius   = 0.13f;
    float smoothing_scale   = particle_radius * 10;
    float h_3               = smoothing_scale*smoothing_scale*smoothing_scale;
    float h_6               = h_3 * h_3;
    float h_9               = h_3 * h_6;
    float K                 = 10.0f;
    float MU                = 1000000.0;
    float MASS              = 0.05f;
    float invMASS           = 1.0f/MASS;
    int N        = int(gl_NumWorkGroups.x*gl_WorkGroupSize.x);
    int index_x  = int(gl_GlobalInvocationID);
    vec4 gravity = vec4(0.0, -9.80, 0.0, 0.0);


    p_force[index_x] = gravity * MASS;


    vec4 position_src = p_position[index_x];
    vec4 velocity_src = p_velocity[index_x];
    float density_src = p_density[index_x];


    for (int tile = 0; tile < num_p; tile+=int(gl_WorkGroupSize.x))
    {
        tmp[gl_LocalInvocationIndex] = p_position[tile + int(gl_LocalInvocationIndex)];
        groupMemoryBarrier();
        barrier();

        for (int i = 0; i < gl_WorkGroupSize.x; i++)
        {
            float delta = length(position_src.xyz - tmp[i].xyz);

            if (delta < smoothing_scale)
            {
                compute_density(delta, MASS, smoothing_scale, h_9, p_density[index_x]);
            }
        }
        groupMemoryBarrier();
        barrier();
    }

    for (int tile = 0; tile < ghost_size; tile+=int(gl_WorkGroupSize.x))
    {
        tmp[gl_LocalInvocationIndex] = ghost_p_position[tile + int(gl_LocalInvocationIndex)];
        groupMemoryBarrier();
        barrier();

        for (int i = 0; i < gl_WorkGroupSize.x; i++)
        {
            float delta = length(position_src.xyz - tmp[i].xyz);

            if (delta < smoothing_scale)
            {
                compute_density(delta, MASS, smoothing_scale, h_9, p_density[index_x]);
            }
        }
        groupMemoryBarrier();
        barrier();
    }

    p_pressure[index_x] = K * (pow(p_density[index_x]/1000.0, 7.0) - 1.0);
    
    for (int tile = 0; tile < num_p; tile+=int(gl_WorkGroupSize.x))
    {
        tmp[gl_LocalInvocationIndex]   = p_position[tile + int(gl_LocalInvocationIndex)];
        den[gl_LocalInvocationIndex]   = p_density[tile + int(gl_LocalInvocationIndex)];
        press[gl_LocalInvocationIndex] = p_pressure[tile + int(gl_LocalInvocationIndex)];
        vel[gl_LocalInvocationIndex]   = p_velocity[tile + int(gl_LocalInvocationIndex)];

        groupMemoryBarrier();
        barrier();

        for (int i = 0; i < gl_WorkGroupSize.x; i++)
        {
            float delta  = length(position_src.xyz - tmp[i].xyz);
            if (delta < smoothing_scale)
            {
                float density_ngh = den[i];
                vec4  deltav = position_src - tmp[i]; 
                
                float pressure_factor = - MASS * MASS/(density_src*density_ngh);

                pressure_factor *= 0.5*(p_pressure[index_x] + press[i]);
                p_force[index_x] += pressure_factor * vec4(KernelGrad(deltav.xyz, smoothing_scale, h_6),0.0);

                float viscocity_C = MASS * MASS / (density_src * density_ngh);
                vec4 viscocity_factor = viscocity_C * MU * (vel[i] - p_velocity[index_x]);

                p_force[index_x] += viscocity_factor * KernelLaplacian(deltav.xyz, smoothing_scale, h_6);

            }
        }
        groupMemoryBarrier();
        barrier();
    }

    for (int tile = 0; tile < ghost_size; tile+=int(gl_WorkGroupSize.x))
    {
        tmp[gl_LocalInvocationIndex]    = ghost_p_position[tile + int(gl_LocalInvocationIndex)];
        //den[gl_LocalInvocationIndex]    = p_density[index_x];
        //press[gl_LocalInvocationIndex]  = p_pressure[index_x];
        normal[gl_LocalInvocationIndex] = ghost_p_normal[tile + int(gl_LocalInvocationIndex)];

        groupMemoryBarrier();
        barrier();


        for (int i = 0; i < gl_WorkGroupSize.x; i++)
        {
            float delta  = length(position_src.xyz - tmp[i].xyz);
            if (delta < smoothing_scale)
            {
                //float density_ngh = den[i];

                vec4  deltav = position_src - tmp[i]; 
                float pressure_factor = - MASS * MASS/(density_src*density_src);

                pressure_factor *= p_pressure[index_x];
                p_force[index_x] += pressure_factor * vec4(KernelGrad(deltav.xyz, smoothing_scale, h_6),0.0);


                float v_normal_solid = dot(velocity_src.xyz, normal[i].xyz);
                vec4 v_ghost = vec4(p_velocity[index_x].xyz - v_normal_solid * normal[i].xyz, 0.0);

                float viscocity_C     = MASS * MASS / (density_src * density_src);
                
                vec4 viscocity_factor = viscocity_C * MU * (v_ghost - p_velocity[index_x]);

                vec4 voscocity_force  = viscocity_factor * KernelLaplacian(deltav.xyz, smoothing_scale, h_6);

                float vf_mod          = length(voscocity_force);
                vec4  vf_u            = voscocity_force/vf_mod;
                
                vec4 vf_force         = voscocity_force;
                //if (vf_mod > 1)
                //    vec4 vf_force = 1.0f * vf_u;
                p_force[index_x] += voscocity_force;

            }
        }
        groupMemoryBarrier();
        barrier();
    }

    for (int i = 0; i < ghost_size; i++)
    {
        float delta  = length(position_src.xyz - ghost_p_position[i].xyz);

        if (delta < smoothing_scale)
        {

            vec4 deltav         = position_src - ghost_p_position[i]; 
            float normal_dist   = dot(deltav.xyz, ghost_p_normal[i].xyz);

            if (normal_dist < 0) //inner
            {
                p_position[index_x] -= vec4(ghost_p_normal[i].xyz * normal_dist, 0.0);
                break;
            }
        }
    }

    compute_velocity(p_velocity[index_x], p_force[index_x].xyz, invMASS, dt);
    compute_position(p_position[index_x], p_velocity[index_x], dt);     


    // Show Ghost Particles
    /*
    for (int i = 0; i < ghost_size; i++)
    {
        p_position[i] = vec4(ghost_p_position[i].xyz, 1.0);
    }  
    */
}