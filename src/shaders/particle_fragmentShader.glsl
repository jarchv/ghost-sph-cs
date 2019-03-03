#version 430

in vec2 txcoord;

layout (location = 0) out vec4 FragColor;

in vec3 Position_worldspace;
uniform vec3  LightPosition_worldspace;

void main()
{
	//vec3 color = vec3(0.1, 0.4, 0.8);
	//FragColor  = vec4(color, 1.0);
	//float s = (1/(1+15.*dot(txcoord, txcoord))-1/16.)
	vec3 LightColor  = vec3(1.0f,1.0f,1.0f);
	float LightPower = 50.0f;

	vec3 MaterialDiffuseColor  = vec3(0.3,0.3,1.0);;
	vec3 MaterialAmbientColor  = vec3(0.5,0.5,0.5) * MaterialDiffuseColor;
	
	float distance = length( LightPosition_worldspace - Position_worldspace );

	FragColor.rgb = MaterialAmbientColor + 
					MaterialDiffuseColor  * LightColor * LightPower / (distance*distance);

	FragColor.a = 1.0;
}