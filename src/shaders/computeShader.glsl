#version 430     

struct Particle
{
    vec3 position;
};

layout (local_size_x = 256) in;
//layout (rgba32f, binding = 0) uniform image2D img_output;

/*
layout(std430, binding = 0) buffer pblock 
{ 
    Particle FluidParticles[]; 
};
*/
layout(std430, binding = 0) buffer pblock 
{ 
    vec4 FluidParticles[]; 
};

layout (location = 0) uniform float dt;
/*
vec4 particles(float sphere_r, ivec2 pixel_coords, float dt)
{
    vec4 pixel = vec4(0.8, 0.8, 0.8, 1.0);
    //ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

    float max_x = 5.0;
    float max_y = 5.0;

    ivec2 dims = imageSize(img_output);

    float x = (float(pixel_coords.x * 2 - dims.x) / dims.x);
    float y = (float(pixel_coords.y * 2 - dims.y) / dims.y);

    vec3 ray_o = vec3 (x * max_x, y * max_y, 0.0);
    vec3 ray_d = normalize(vec3 (0.0, 0.0, -8.0));

    for (int i = 0; i < 2; i++)
    {
        vec3 sphere_c = vec3 (FluidParticles[i].position.x, FluidParticles[i].position.y + dt, -10.0+float(i*6));
        //vec3 sphere_c = vec3 (-1.0 + float(i*2.0), 0.0 + dt, -10.0+float(i*6));
        //float sphere_r = 1.0;

        vec3 omc = ray_o - sphere_c;
        float b = dot (ray_d, omc);
        float c = dot (omc, omc) - sphere_r * sphere_r;

        float bsqmc = b * b - c;

        if (bsqmc >= 0.0)
        {
            float factor = (bsqmc + 0.1f)/(sphere_r * sphere_r);
            
            if (factor > 1)
                factor = 1;

            pixel = vec4 (1.0, 0.3, 0.3, 1.0)*factor;
        }
             
    }
    return pixel;   
    //imageStore (img_output, pixel_coords, pixel);  
}
*/
//uniform float dt;

void main()
{
    int N = int(gl_NumWorkGroups.x*gl_WorkGroupSize.x);
    int index = int(gl_GlobalInvocationID);

    //vec3 position = FluidParticles[index].xyz;
    FluidParticles[index].xyz += vec3(dt, 0.0, 0.0);

    //for(int i = 0; i < N; i++)
    //{
    //    FluidParticles[index].xyz[i] += vec3(dt, 0.0, 0.0);;
    //}
    //FluidParticles[index].position.xyz += vec3(dt, 0.0, 0.0);
    //vec3 position = FluidParticles.position[index].xyz;
    //vec3 position = FluidParticles.position[index].xyz;
    //ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

    //vec4 pixel =  particles(0.5, pixel_coords, dt);
    //imageStore(img_output, pixel_coords, pixel);  

    /*
    vec4 pixel = vec4(0.8, 0.8, 0.8, 1.0);
    ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

    float max_x = 5.0;
    float max_y = 5.0;

    ivec2 dims = imageSize(img_output);

    float x = (float(pixel_coords.x * 2 - dims.x) / dims.x);
    float y = (float(pixel_coords.y * 2 - dims.y) / dims.y);

    vec3 ray_o = vec3 (x * max_x, y * max_y, 0.0);
    vec3 ray_d = vec3 (0.0, 0.0, -1.0);

    vec3 sphere_c = vec3 (0.0, 0.0, -10.0);
    float sphere_r = 1.0;

    vec3 omc = ray_o - sphere_c;
    float b = dot (ray_d, omc);
    float c = dot (omc, omc) - sphere_r * sphere_r;

    float bsqmc = b * b - c;

    float t = 10000.0;

    if (bsqmc >= 0.0)
    {
        float factor = (bsqmc + 0.2f)/(sphere_r * sphere_r);
        
        if (factor > 1)
            factor = 1;

        pixel = vec4 (1.0, 0.3, 0.3, 1.0)*factor;
    }

    imageStore (img_output, pixel_coords, pixel);
    */
}