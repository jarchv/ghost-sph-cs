#version 330

precision mediump float;

// Interpolated values from the vertex shaders
in vec3 fragmentColor;
//in vec2 UV;
// Out data
out vec4 color;

// Values that stay constant for whole mesh
//uniform sampler2D TextureSampler;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

float cosTheta;	

// Values that stay constant for the whole mesh.
uniform vec3  LightPosition_worldspace;
uniform float Transparent;

void main()
{
    //color = vec3(0.7,0.0,0);
    vec3 LightColor = vec3(1.0f,1.0f,1.0f);
    float LightPower = 80.0f;
    
    //std::cout << "v_v4FillColor " << v_v4FillColor.x << std::endl;
    // Material properties
    vec3 MaterialDiffuseColor  = fragmentColor;
    //vec3 MaterialDiffuseColor  = vec3(0.2,0.2,0.6);
    vec3 MaterialAmbientColor  = vec3(0.5,0.5,0.5) * MaterialDiffuseColor;
    vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);

    // Distance to the light
    float distance = length( LightPosition_worldspace - Position_worldspace );

    // Normal of the computed fragment, in camera space
    vec3 n = normalize( Normal_cameraspace );

    // Direction of the light (from the fragment to the light)
    vec3 l = normalize( LightDirection_cameraspace );
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	// - light is at the vertical of the triangle -> 1
	// - light is perpendicular to the triangle -> 0
    // - light is behind the triangle -> 0
    
    cosTheta = dot(n, l);
    cosTheta = clamp(cosTheta, 0.0, 1.0);


	// Eye vector (towards the camera)
    vec3 E = normalize(EyeDirection_cameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
    float cosAlpha = clamp( dot( E,R ), 0.0,1.0 );  

	color.rgb = 
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor  * LightColor * LightPower * cosTheta / (distance*distance); +
		// Specular : reflective highlight, like a mirror
        MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);
    
    color.a = 1.0;

    //color.rgb = sphereColors;
    //color.a   = color.a   + 1.0;
    //color.a = 1.0;
}