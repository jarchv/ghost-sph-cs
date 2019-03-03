#version 430

in vec2 txcoord;

layout (location = 0) out vec4 FragColor;

in vec3 Position_worldspace;
uniform vec3  LightPosition_worldspace;

uniform sampler2D u_texture;

void main()
{
	float d = clamp(dot(txcoord, txcoord), 0, 1);
	vec3 LightColor  = vec3(1.0f,1.0f,1.0f);
	float LightPower = 50.0f;

	vec3 MaterialDiffuseColor  = vec3(0.0,0.46,0.74)*(1-d);
	vec3 MaterialAmbientColor  = vec3(0.9,0.9,0.9) * MaterialDiffuseColor;
	
	float distance = length( LightPosition_worldspace - Position_worldspace );

	if (d > 0.5)
		discard;
	else
	{
		FragColor = vec4(MaterialAmbientColor, 1.0) + vec4(MaterialDiffuseColor  * LightColor * LightPower / (pow(distance,10)),1.0);
	}
}