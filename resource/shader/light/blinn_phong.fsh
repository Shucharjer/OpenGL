#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
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
    sampler2D normal;
};

uniform vec3 view_pos;
uniform Material material;

uniform DirectionalLight dir_light;
uniform PointLight point_lights[4];
//uniform SpotLight spot_lights[];

vec3 calDirLight(DirectionalLight light, vec3 ambient, vec3 diffuse, vec3 specular, vec3 normal, vec3 view_dir);
vec3 calPoiLight(PointLight light, vec3 ambient, vec3 diffuse, vec3 specular, float shininess, vec3 normal, vec3 view_dir);
vec3 calSpoLight(SpotLight light, vec3 ambient, vec3 diffuse, vec3 specular, float shininess, vec3 normal, vec3 view_dir);

void main()
{
    vec3 ambient = vec3(texture(material.ambient, TexCoords));
    vec3 diffuse = vec3(texture(material.diffuse, TexCoords));
    vec3 specular = vec3(texture(material.specular, TexCoords));
    float shininess = 32.0;
    vec3 normal = vec3(texture(material.normal, TexCoords));

    vec3 view_dir = normalize(view_pos - FragPos);

    vec3 color = vec3(0.0);

    //color += calDirLight(dir_light, ambient, diffuse, specular, normal, view_dir);
    for (int i = 0; i < 4; i++)
        color += calPoiLight(point_lights[i], ambient, diffuse, specular, shininess, Normal, view_dir);
    FragColor = vec4(color, 1.0);
}

vec3 calDirLight(DirectionalLight light, vec3 ambient, vec3 diffuse, vec3 specular, float shininess, vec3 normal, vec3 view_dir)
{
    vec3 light_dir = normalize(-light.direction);
    vec3 half_way = normalize(light_dir + view_dir);

    vec3 a = ambient * light.ambient;
    vec3 d = diffuse * light.diffuse * max(dot(normal, light_dir), 0.0);
    vec3 s = specular * light.specular * pow(max(dot(view_dir, half_way), 0.0), shininess);
    
    return a + d + s;
}

vec3 calPoiLight(PointLight light, vec3 ambient, vec3 diffuse, vec3 specular, float shininess, vec3 normal, vec3 view_dir)
{
    vec3 light_dir = normalize(light.position - FragPos);
    vec3 half_way = normalize(light_dir + view_dir);

    vec3 a = ambient * light.ambient;
    vec3 d = diffuse * light.diffuse * max(dot(normal, light_dir), 0.0);
    vec3 s = specular * light.specular * pow(max(dot(view_dir, half_way), 0.0), shininess);

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + (light.linear + light.quadratic *  distance) * distance);

    return (a + d + s) * attenuation;
}

vec3 calSpoLight(SpotLight light, vec3 ambient, vec3 diffuse, vec3 specular, float shininess, vec3 normal, vec3 view_dir)
{
    vec3 light_dir = normalize(light.position - FragPos);
    vec3 half_way = normalize(light_dir + view_dir);

    vec3 color = vec3(0.0);

    vec3 a = ambient * light.ambient;
    vec3 d = diffuse * light.diffuse * max(dot(normal, light_dir), 0.0);
    vec3 s = specular * light.specular * pow(max(dot(view_dir, half_way), 0.0), shininess);

    float theta = dot(light_dir, light.direction);
    if (theta > cos(light.outerCutoffAngle))
    {
        float epsilon = cos(light.cutoffAngle) - cos(light.outerCutoffAngle);
        float intensity = clamp((theta - cos(light.outerCutoffAngle)) / epsilon, 0.0, 1.0);
        color += (d + s) * intensity;
    }
    color += a;
    return color;
}
