#version 430

in vec2 txcoord;

layout (location = 0) out vec4 FragColor;

void main()
{
	vec3 color   = vec3(0.1, 0.4, 0.8);
	//float s 	 = (1/(1+2.*dot(txcoord, txcoord)) - 1/3.0); // Center point will be white
	
	FragColor = vec4(color, 1.0);
}