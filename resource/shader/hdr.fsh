#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D hdrBuffer;
// 曝光度
uniform float exposure;

uniform float gamma;

void main()
{
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;
    // 色调映射
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
    // gamma校正
    mapped = pow(mapped, vec3(1.0 / gamma));

    FragColor = vec4(hdrColor, 1.0);
}
