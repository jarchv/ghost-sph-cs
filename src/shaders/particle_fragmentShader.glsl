#version 430

in vec2 txcoord;

out vec4 FragColor;

in vec3 Position_worldspace;
uniform vec3  LightPosition_worldspace_p;

uniform sampler2D u_texture;

void main()
{
	float d = clamp(dot(txcoord, txcoord), 0, 1);
	vec3 LightColor  = vec3(1.0f,1.0f,1.0f);
	float LightPower = 500.0f;

	vec3 MaterialDiffuseColor  = vec3(0.0,0.46,0.74)*(1-d);
	vec3 MaterialAmbientColor  = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;
	
	float distance = length( LightPosition_worldspace_p - Position_worldspace );

	if (d > 0.5)
		discard;
	else
	{
		//FragColor = vec4(MaterialAmbientColor, 1.0) + vec4(MaterialDiffuseColor  * LightColor * LightPower / (pow(distance,2)),1.0);
		FragColor.rgb = MaterialAmbientColor + MaterialDiffuseColor  * LightColor * LightPower / (distance * distance);
	}

	FragColor.a = 0.75;
}