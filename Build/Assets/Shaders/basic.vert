#version 430 core 
in layout (location = 0) vec3 vposition; //0
//in layout (location = 1) vec3 vcolor; //1
in layout (location = 1) vec2 vuV; //2

out vec3 color;
out vec2 uV;

uniform float scale;
uniform mat4 mvp;

void main()
{
	//color = vcolor;
	uV = vuV;

	vec4 tposition = mvp * vec4(vposition * scale, 1.0);
	gl_Position = tposition;
}
