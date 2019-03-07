#version 430

in vec2 txcoord;

out vec4 FragColor;

in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;


uniform vec3  LightPosition_worldspace_p;
uniform sampler2D u_texture;

void main()
{
	float d = clamp(dot(txcoord, txcoord), 0, 1);
	vec3 LightColor  = vec3(1.0f,1.0f,1.0f);
	float LightPower = 40.0f;

	vec3 MaterialDiffuseColor  = vec3(0.0,0.46,0.74)*(1-d);// : illumination
	vec3 MaterialAmbientColor  = vec3(0.5,0.5,0.5) * MaterialDiffuseColor;

	vec3 n = normalize(Normal_cameraspace);
	vec3 l = normalize(LightDirection_cameraspace);

	float distance = length(LightPosition_worldspace_p - Position_worldspace);
	float cosTheta = dot(n , l);
	cosTheta       = clamp(cosTheta, 0.0, 1.0);
	if (d > 0.3)
		discard;
	else
	{
		float factor = cosTheta * LightPower/ distance;
		if (factor > 1.3)
			factor = 1.3;
		FragColor.rgb = MaterialAmbientColor + MaterialDiffuseColor  * LightColor * factor;
	}

	FragColor.a = 1.0*(1-d);
}