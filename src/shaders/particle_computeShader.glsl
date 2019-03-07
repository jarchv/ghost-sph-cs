#version 430     

float pradius   = 0.13f;
float h         = pradius * 3; //h
float h_3       = h*h*h;
float h_6       = h_3 * h_3;
float h_9       = h_3 * h_6;
float K         = 0.1f;
float mu        = 0.005f;
float MASS      = 0.02f;
float invMASS   = 1.0f/MASS;
float eps       = 1e-12;

struct Particle
{
    vec4 v;
    vec4 f;

    float dty0;
    float dty;
    float press;
};

layout (local_size_x = 512) in;

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
    vec4 ghost_p_ghost_normal[];
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

float W_poly(float delta, float h, float h_9)
{
    float dif    = (h * h  - delta * delta);
    float factor = dif * dif * dif;

    return factor * 315.0 /(64.0 * h_9 * 3.14159);
}

vec3 gradW_press(vec3 deltav, float h, float h_6)
{
    float r = sqrt(dot(deltav,deltav));

    if (r == 0)
        return vec3(0.0,0.0,0.0);

    float factor = -45.0 *  (h - r) * (h - r)/ (3.14159 * h_6);
    
    return  factor * normalize(deltav); 
}

float lapW_visco(float delta, float h, float h_6)
{
    return 45.0 * (h - delta)/ (3.14159 * h_6);
}

void compute_density(float delta, float MASS, float h, float h_9, inout float density)
{
    density += MASS * W_poly(delta, h, h_9);
}

vec4 pressure_force(float Pi, float Pj, float rhoi, float rhoj, vec4 deltav)
{
    float press_factor = - MASS * MASS;
    press_factor      *= (Pi/(rhoi * rhoi + eps) + Pj/(rhoj * rhoj + eps));

    return  vec4(gradW_press(deltav.xyz, h, h_6),0.0) * press_factor;
}

void XSPH(  inout vec4 vi, 
            vec4 vj, 
            float rhoj, 
            float delta,
            float mu_var)
{
    vi += mu_var * (MASS / rhoj) * (vj - vi) * lapW_visco(delta, h, h_6);
}

float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))*43758.5453123);
}

shared vec4  tmp[gl_WorkGroupSize.x];
shared vec4  vel[gl_WorkGroupSize.x];
shared float den[gl_WorkGroupSize.x];
shared float press[gl_WorkGroupSize.x];
shared vec4  ghost_normal[gl_WorkGroupSize.x];


void main()
{
    int N        = int(gl_NumWorkGroups.x*gl_WorkGroupSize.x);
    int index_x  = int(gl_GlobalInvocationID);
    vec4 gravity = vec4(0.0, -9.80, 0.0, 0.0);

    if (p_position[index_x].y > 10.0)
    {    
        p_velocity[index_x] = vec4(0.0,-15.0,0.0,0.0);
        compute_position(p_position[index_x], p_velocity[index_x], dt);
        //p_position[index_x].w = 0.0;
        return;
    }

    if (p_position[index_x].y < -30.0)
    {    
        float dtheta  = random(p_position[index_x].xz);
        float dradius = random(p_position[index_x].xz);

        p_position[index_x].x  = 0.5 * dradius * cos(dtheta * 2.0 * 3.14159);
        p_position[index_x].y += 33.0;
        p_position[index_x].z  = 0.5 * dradius * sin(dtheta * 2.0 * 3.14159) + 20.0;
        p_velocity[index_x]    = vec4(0.0,-20.0,0.0,0.0);
        return;
    }

    p_force[index_x]   = gravity * MASS;
    p_density[index_x] = 0.0; 

    vec4 position_src  = p_position[index_x];

    float delta;


    /*
    *  Compute for nearest liquid particles
    *  ===================================
    */  

    for (int tile = 0; tile < num_p; tile+=int(gl_WorkGroupSize.x))
    {
        tmp[gl_LocalInvocationIndex] = p_position[tile + int(gl_LocalInvocationIndex)];
        groupMemoryBarrier();
        barrier();

        for (int i = 0; i < gl_WorkGroupSize.x; i++)
        {
            delta = length(position_src.xyz - tmp[i].xyz);

            if (delta < h)
            {
                /*
                * Density Accumulator
                * ===================
                */
                compute_density(delta, MASS, h, h_9, p_density[index_x]);
            }
        }
        groupMemoryBarrier();
        barrier();
    }

    /*
    *  Compute for nearest solid particles
    *  ===================================
    */  

    for (int tile = 0; tile < ghost_size; tile+=int(gl_WorkGroupSize.x))
    {
        tmp[gl_LocalInvocationIndex] = ghost_p_position[tile + int(gl_LocalInvocationIndex)];
        groupMemoryBarrier();
        barrier();

        for (int i = 0; i < gl_WorkGroupSize.x; i++)
        {
            delta = length(position_src.xyz - tmp[i].xyz);

            if (delta < h)
            {
                /*
                * Density Accumulator
                * ===================
                */
                compute_density(delta, MASS*5, h, h_9, p_density[index_x]);
            }
        }
        groupMemoryBarrier();
        barrier();
    }

    float density_src = p_density[index_x];
    p_pressure[index_x] = K * (pow(density_src/1000.0, 7.0) - 1.0);
    
    float density_ngh;
    float press_factor;
    vec4  deltav;

    for (int tile = 0; tile < num_p; tile+=int(gl_WorkGroupSize.x))
    {
        tmp[gl_LocalInvocationIndex]   = p_position[tile + int(gl_LocalInvocationIndex)];
        den[gl_LocalInvocationIndex]   = p_density[tile  + int(gl_LocalInvocationIndex)];
        press[gl_LocalInvocationIndex] = p_pressure[tile + int(gl_LocalInvocationIndex)];

        groupMemoryBarrier();
        barrier();

        for (int i = 0; i < gl_WorkGroupSize.x; i++)
        {
            delta  = length(position_src.xyz - tmp[i].xyz);
            if (delta < h)
            {
                density_ngh  = den[i];
                deltav       = position_src - tmp[i]; 

                /*
                * Compute ṕressure force
                * ======================
                */

                vec4 pforce  = pressure_force(  p_pressure[index_x],
                                                press[i],
                                                density_src,
                                                density_ngh,
                                                deltav);
                p_force[index_x] += pforce;
                //press_factor = - MASS * MASS;

                //press_factor      *= (p_pressure[index_x]/(density_src * density_src + eps) + press[i]/(eps + density_ngh*density_ngh));
                //p_force[index_x]  += press_factor * vec4(gradW_press(deltav.xyz, h, h_6),0.0);

            }
        }
        groupMemoryBarrier();
        barrier();
    }
    
    for (int tile = 0; tile < ghost_size; tile+=int(gl_WorkGroupSize.x))
    {
        tmp[gl_LocalInvocationIndex]    = ghost_p_position[tile + int(gl_LocalInvocationIndex)];
        groupMemoryBarrier();
        barrier();


        for (int i = 0; i < gl_WorkGroupSize.x; i++)
        {
            
            delta  = length(position_src.xyz - tmp[i].xyz);
            if (delta < h)
            {
                deltav       = position_src - tmp[i]; 
                
                /*
                * Compute ṕressure force
                * ======================
                */
                
                vec4 pforce  = pressure_force(  p_pressure[index_x],
                                                p_pressure[index_x],
                                                density_src,
                                                density_src,
                                                deltav);
                p_force[index_x]    += pforce;
                
                //press_factor = - MASS * MASS;

                //press_factor     *= 2 * (p_pressure[index_x]/(density_src * density_src + eps));
                //p_force[index_x] += press_factor * vec4(gradW_press(deltav.xyz, h, h_6),0.0);

            }
        }
        groupMemoryBarrier();
        barrier();
    }
    
    compute_velocity(p_velocity[index_x], p_force[index_x].xyz, invMASS, dt);

    vec4 velocity_src  = p_velocity[index_x];
    float v_ghost_normal_solid;



    
    /*
    *  Compute for nearest liquid particles
    *  ===================================
    */  

    for (int tile = 0; tile < num_p; tile+=int(gl_WorkGroupSize.x))
    {
        tmp[gl_LocalInvocationIndex] = p_position[tile + int(gl_LocalInvocationIndex)];
        vel[gl_LocalInvocationIndex] = p_velocity[tile + int(gl_LocalInvocationIndex)];

        groupMemoryBarrier();
        barrier();


        for (int i = 0; i < gl_WorkGroupSize.x; i++)
        {
            delta  = length(position_src.xyz - tmp[i].xyz);
            if (delta < h)
            {
                /*
                *  Artificial Viscosity
                *  ====================
                */
                XSPH(p_velocity[index_x], vel[i], density_src, delta, mu);            
            }
        }
        groupMemoryBarrier();
        barrier();
    }

    /*
    *  Compute for nearest solid particles
    *  ===================================
    */

    vec4  Vghost;
    float Vliquid_N;

    for (int tile = 0; tile < ghost_size; tile+=int(gl_WorkGroupSize.x))
    {
        tmp[gl_LocalInvocationIndex]          = ghost_p_position[tile + int(gl_LocalInvocationIndex)];
        ghost_normal[gl_LocalInvocationIndex] = ghost_p_ghost_normal[tile + int(gl_LocalInvocationIndex)];

        groupMemoryBarrier();
        barrier();


        for (int i = 0; i < gl_WorkGroupSize.x; i++)
        {
            delta  = length(position_src.xyz - tmp[i].xyz);
            if (delta < h)
            {
                /*
                *  Artificial Viscosity
                *  ====================
                *
                * Vghost = Vsolid_N + Vliquid_T 
                * Vghost = Vliquid_T (Vsolid = 0)
                *
                */

                Vliquid_N = dot(velocity_src.xyz, ghost_normal[i].xyz);
                Vghost    = vec4(velocity_src.xyz - Vliquid_N * ghost_normal[i].xyz, 0.0);

                XSPH(p_velocity[index_x], Vghost, density_src, delta, mu *50.0);            
            }
        }
        groupMemoryBarrier();
        barrier();
    }

    

    compute_velocity(p_velocity[index_x], p_force[index_x].xyz, invMASS, dt);
    compute_position(p_position[index_x], p_velocity[index_x], dt);     

    /*
    * Projection of points to the surface
    * ===================================
    */
    for (int i = 0; i < ghost_size; i++)
    {
        float delta  = length(position_src.xyz - ghost_p_position[i].xyz);

        if (delta < h*2.0)
        {

            vec4 deltav             = position_src - ghost_p_position[i]; 
            float ghost_normal_dist = dot(deltav.xyz, ghost_p_ghost_normal[i].xyz);

            if (ghost_normal_dist < 0) //inner
            {
                p_position[index_x] -= vec4(ghost_p_ghost_normal[i].xyz * (ghost_normal_dist), 0.0);
                break;
            }
        }
    }
    // Show Ghost Particles
    /*
    for (int i = 0; i < ghost_size; i++)
    {
        p_position[i] = vec4(ghost_p_position[i].xyz, 1.0);
    }  
    */
}