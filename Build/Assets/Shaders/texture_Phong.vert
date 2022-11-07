#version 430 core 
in layout (location = 0) vec3 vposition;	//0
in layout (location = 1) vec2 vuV;			//1
in layout (location = 2) vec3 vnormal;		//2
in layout (location = 3) vec3 vtbn;		//2

out vec3 position;
out vec3 normal;
out vec2 uV;
out mat3 tbn;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{


	//color = vcolor;
	// create model view matrix
	mat4 model_view = view * model;
	// transform normals to view space
	normal = mat3(model_view) * vnormal;

	position = vec3(model_view * vec4(vposition, 1));
	uV = vuV;
	
	//vec4 tposition = mvp * vec4(vposition * scale, 1.0);
	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}
