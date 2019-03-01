#version 430

/*
in vec2 fragTexCoord; //this is the texture coord
uniform sampler2D img;
out vec4 fc;

void main()
{
    fc = texture(img, fragTexCoord);
}
*/

in vec2 txcoord;

layout (location = 0) out vec4 FragColor;

void main()
{
	float s = (1/(1+15.*dot(txcoord, txcoord)) - 1/16.0);
	FragColor = s * vec4(0.3, 0.3, 1.0, 1);
}