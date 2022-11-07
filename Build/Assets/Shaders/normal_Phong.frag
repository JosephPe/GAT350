#version 430 core

in vec3 position;
in vec2 uV;
in mat3 tbn;

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
vec2 uv_tiling;
vec2 uv_offset;
};

uniform Light light;
uniform Material material;


layout (binding = 0) uniform sampler2D diffuseMap;
layout (binding = 1) uniform sampler2D normalMap;

void phong(vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	ambient = light.ambient * material.color;

	vec3 light_dir = normalize(vec3(light.position) - position);

	//calculate light intensity with dot product (nromal * light direction)
	float intensity = max(dot(light_dir, normal), 0);
	 diffuse = light.color * material.color * intensity;

	//specular
	 specular = vec3(0);
	if (intensity > 0)
	{
	vec3 reflection = reflect(-light_dir, normal);
	vec3 view_dir = normalize(-vec3(position));
	intensity = max(dot(reflection, view_dir), 0);
	intensity = pow(intensity, material.shininess);
	specular = light.color * material.color * intensity;
	}
}

void main()
{
//transform positions to view space
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec2 vuV = (uV * material.uv_tiling) + (material.uv_offset);

	vec3 normal = texture(normalMap, vuV).rgb;

	normal = normal * 2 - 1;
	normal = normalize(tbn * normal);

	phong(position, normal, ambient, diffuse, specular);

	//uV = vuV;
	//vec4 position = model_view * vec4(vposition, 1);	


	//color = ambient + diffuse + specular;
	//fcolor = vec4(color * tint, 1.0);
	//fcolor = texture(texture1, uV);//vec4(ambient + diffuse, 1) * texture(textureSampler, uV) + vec4(specular, 1);

	//vec4 texture_color = mix(texture(texture1, vuV), texture(texture2, vuV), 0.5);

	vec4 texture_color = texture(diffuseMap, vuV);
	//fcolor = texture_color;
	fcolor = vec4(ambient + diffuse, 1) * texture_color + vec4(specular, 1);
}
