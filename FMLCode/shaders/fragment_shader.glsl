#version 330 core

uniform sampler2D texture1;

in vec2 TexCoords;

out vec4 FragColor;

uniform vec4 source;

void main()
{
    FragColor = texture(texture1, vec2((TexCoords.x * source.z) + source.x, (TexCoords.y * source.w) + source.y));
}
