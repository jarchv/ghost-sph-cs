#version 430

layout (location = 1) uniform mat4 View;
layout (location = 2) uniform mat4 Projection;
layout (location = 3) uniform mat4 Model;

layout (points) in;

layout (triangle_strip, max_vertices = 4) out;

out vec2 txcoord;
out vec3 Position_worldspace;
out vec3 LightDirection_cameraspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;

uniform vec3  LightPosition_worldspace;

void main()
{
	Position_worldspace = (Model * vec4(gl_in[0].gl_Position.xyz,1)).xyz;
	
	// Vector que va del vertice hacia la camara
	// En el espacio camara la posicion de la camara es 0,0,0
	vec3 vertexPosition_cameraspace = ( View * Model * vec4(gl_in[0].gl_Position.xyz,1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	// Vector que va del vertice hacia la camara( espacio camara) No hay M porque no transformamos la luz.
	vec3 LightPosition_cameraspace = ( View * vec4(LightPosition_worldspace,1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
	
	// Normal despues de la transformacion 
    Normal_cameraspace = ( View * Model * vec4(gl_in[0].gl_Position.xyz - vec3(0.0,gl_in[0].gl_Position.y,20.0),0)).xyz;


	vec4 pos = View*gl_in[0].gl_Position;
	
	txcoord = vec2(-1,-1);
	gl_Position = Projection*(pos+0.2*vec4(txcoord,0,0));
	EmitVertex();

	txcoord = vec2( 1,-1);
	gl_Position = Projection*(pos+0.2*vec4(txcoord,0,0));
	EmitVertex();

	txcoord = vec2(-1, 1);
	gl_Position = Projection*(pos+0.2*vec4(txcoord,0,0));
	EmitVertex();

	txcoord = vec2( 1, 1);
	gl_Position = Projection*(pos+0.2*vec4(txcoord,0,0));
	EmitVertex();
}