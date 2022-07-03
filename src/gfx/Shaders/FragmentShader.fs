#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in float ShadeFactor;

uniform sampler2D texture1;

void main()
{
    vec4 texColor = texture(texture1, TexCoord);
    if (texColor.a < 0.1)
        discard;
    FragColor = vec4(vec3(texColor)*ShadeFactor, texColor.a);  
} 
