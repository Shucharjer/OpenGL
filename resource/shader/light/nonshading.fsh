#version 330 core

in vec2 texture_coords;

out vec4 FragColor;

uniform sampler2D ambient;

void main()
{
    FragColor = vec3(texture(ambient, texture_coords));
}