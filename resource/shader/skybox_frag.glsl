#version 330 core

in vec3 texture_coords;

out vec4 FragColor;

uniform samplerCube skybox_texture;

void main()
{
    FragColor = texture(skybox_texture, texture_coords);
}