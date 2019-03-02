#version 430

/*
location = 0, refers to the buffer we use to feed the VertexPosition_modelspace
attibrute.

Each vertex can have numerous attributes : A position, one or several colours, 
one or several texture coordinates, lots of other things. 
OpenGL doesn’t know what a colour is : it just sees a vec3. 
So we have to tell him which buffer corresponds to which input. 
We do that by setting the layout to the same value as the first parameter 
to glVertexAttribPointer. The value “0” is not important, 
it could be 12 (but no more than glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &v) ), 
the important thing is that it’s the same number on both sides.

“vertexPosition_modelspace” could have any other name. It will contain
the position of the vertex for each run of the vertex shader.

“in” means that this is some input data. Soon we’ll see the “out” keyword.

*/

layout(location = 4) in vec3 vertexPosition_modelspace;
layout(location = 5) in vec3 vertexColor;
layout(location = 6) in vec3 vertexNormal_modelspace;

// Output data: will be interpolated for each fragment
out vec3 fragmentColor;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

// Values that stay constant for whole mesh
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightPosition_worldspace;

void main()
{

    // Output position of the vertex, in clip space : MVP * position
    gl_Position   = MVP * vec4(vertexPosition_modelspace, 1);// + MVP * vec4(spherevertex, 1);

	// La posicion del vertice solamente despues de la transformacion espacial (rotacion)
	Position_worldspace = (M * vec4(vertexPosition_modelspace,1)).xyz;
	
	// Vector que va del vertice hacia la camara
	// En el espacio camara la posicion de la camara es 0,0,0
	vec3 vertexPosition_cameraspace = ( V * M * vec4(vertexPosition_modelspace,1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	// Vector que va del vertice hacia la camara( espacio camara) No hay M porque no transformamos la luz.
	vec3 LightPosition_cameraspace = ( V * vec4(LightPosition_worldspace,1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
	
	// Normal despues de la transformacion 
    Normal_cameraspace = ( V * M * vec4(vertexNormal_modelspace,0)).xyz;

    // vertexColor
    fragmentColor = vertexColor;
}