#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutoffAngle;
    float outerCutoffAngle;
};

struct Material
{
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;

uniform DirectionalLight dir_lights[1];
uniform PointLight point_lights[4];
//uniform SpotLight spot_lights[];

vec3 calDirLight(DirectionalLight light, vec3 ambient, vec3 diffuse, vec3 specular, vec3 normal, vec3 view_dir);

void main()
{
    vec3 ambient = vec3(texture(material.ambient, TexCoords));
    vec3 diffuse = vec3(texture(material.diffuse, TexCoords));
    vec3 specular = vec3(texture(material.specular, TexCoords));
    gl_FragColor = vec4(1.0);
}

vec3 calDirLight(DirectionalLight light, vec3 ambient, vec3 diffuse, vec3 specular, vec3 normal, vec3 view_dir)
{
    vec3 light_dir = normalize(-light.direction);
    return vec3(1.0);
}
