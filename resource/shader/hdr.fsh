#version 330 core

in vec2 TexCoords;

uniform sampler2D hdr_color_buffer;
// 曝光度
uniform float exposure;

uniform float gamma;

void main()
{
    vec3 hdr_color = texture(hdr_color_buffer, TexCoords).rgb;
    // 色调映射
    vec3 mapped = vec3(1.0) - exp(-hdr_color * exposure);
    // gamma校正
    mapped = pow(mapped, vec3(1.0 / gamma));

    gl_FragColor = vec4(hdr_color, 1.0);
}
