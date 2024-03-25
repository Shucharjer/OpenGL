#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D texture_ambient;

void main()
{
    FragColor = vec4(vec3(texture(texture_ambient, TexCoords)), 1.0);
}