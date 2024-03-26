#version 330 core

in vec3 texture_coords;

uniform samplerCube skybox_texture;

void main()
{
    gl_FragColor = texture(skybox_texture, texture_coords);
}