#version 430

//layout (location = 0) in vec2 vp;
//layout (location = 1) in vec2 vt;

//out vec2 fragTexCoord;

//uniform mat4 MVP;
//uniform mat4 V;
//uniform mat4 M;

layout(location = 0) in vec4 vposition;

void main()
{
  //fragTexCoord = vt;                                        
  //gl_Position = vec4 (vp, 0.0, 1.0);
  gl_Position = vposition;
}