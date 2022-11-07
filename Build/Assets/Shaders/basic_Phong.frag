#version 430 core

in vec3 position;
in vec3 normal;
in vec2 uV;

out vec4 fcolor;

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

uniform sampler2D textureSampler;

void main()
{
//transform positions to view space
	vec3 ambient = light.ambient * material.color;

	vec3 light_dir = normalize(vec3(light.position) - position);

	//calculate light intensity with dot product (nromal * light direction)
	float intensity = max(dot(light_dir, normal), 0);
	vec3 diffuse = light.color * material.color * intensity;

	//specular
	vec3 specular = vec3(0);
	if (intensity > 0)
	{
	vec3 reflection = reflect(-light_dir, normal);
	vec3 view_dir = normalize(-vec3(position));
	intensity = max(dot(reflection, view_dir), 0);
	intensity = pow(intensity, material.shininess);
	specular = light.color * material.color * intensity;
	}


	//uV = vuV;
	//vec4 position = model_view * vec4(vposition, 1);


	//color = ambient + diffuse + specular;
	//fcolor = vec4(color * tint, 1.0);
	fcolor = texture(textureSampler, uV);//vec4(ambient + diffuse, 1) * texture(textureSampler, uV) + vec4(specular, 1);
}
