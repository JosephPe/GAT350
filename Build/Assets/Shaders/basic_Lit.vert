#version 430 core 
in layout (location = 0) vec3 vposition; //0
//in layout (location = 1) vec3 vcolor; //1
in layout (location = 1) vec2 vuV; //1
in layout (location = 2) vec3 vNormal; //3

out vec2 uV;
out vec3 color;

struct Light
{
vec3 ambient;
vec3 color;
vec4 position;
};

struct Material
{
vec3 color;
float shininess;
};

uniform Light light;
uniform Material material;

uniform float model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
uV = vuV;

vec3 ambient = light.ambient * material.color;
	//color = vcolor;
	// diffuse 
	// create model view matrix
	mat4 model_view = view * model;
	// transform normals to view space
	vec3 normal = mat3(model_view) * vnormal;
	//transform positions to view space
	vec3 light_dir = normalize(vec3(light.position - position));

	//calculate light intensity with dot product (nromal * light direction)
	float intensity = max(dot(light_dir, normal), 0);
	vec3 diffuse = light.color * material.color * intensity;

	//specular
	vec3 specular = vec3(0);
	if (intensity > 0)
	{
	vec3 reflection = reflect(-light_dir, normal);
	vec3 view_dir = normalize(-vec(position));
	intensity = max(dot(reflection, view_dir), 0);
	intensity = pow(intensity, material.shininess);
	specular = light.color * material.color * intensity;
	}


	uV = vuV;
	vec4 position = model_view * vec4(vposition, 1);


	color = ambient + diffuse + specular;

	//vec4 tposition = mvp * vec4(vposition * scale, 1.0);
	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}
