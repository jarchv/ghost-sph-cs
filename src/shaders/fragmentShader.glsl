#version 430

in vec2 txcoord;
layout (location = 0) out vec4 FragColor;

void main()
{
	float s = (1/(1+15.*dot(txcoord, txcoord)) - 1/16.0); // Center point will be white
	FragColor = s*vec4(0.3, 0.3, 1.0, 0.5);
}