#version 430

in vec2 fragTexCoord; //this is the texture coord
uniform sampler2D img;
out vec4 fc;

void main()
{
    fc = texture(img, fragTexCoord);
}
