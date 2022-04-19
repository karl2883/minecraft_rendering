#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in float ShadeFactor;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoord) * ShadeFactor;
} 
