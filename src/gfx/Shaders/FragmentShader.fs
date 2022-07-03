#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec4 ViewSpace;
in float ShadeFactor;

uniform sampler2D texture1;
uniform int FogStart;
uniform int FogEnd;

const vec3 fogColor = vec3(0.2, 0.3, 0.3);

void main()
{
    vec4 texColor = texture(texture1, TexCoord);
    if (texColor.a < 0.1)
        discard;
    texColor = vec4(vec3(texColor)*ShadeFactor, texColor.a); 
    float dist = length(ViewSpace);
    float fogFactor = (FogEnd - dist)/(FogEnd-FogStart);
    fogFactor = clamp(fogFactor, 0.0, 1.0);
    if (fogFactor == 0.0)
        discard;
    vec3 fogTexColor = mix(fogColor, vec3(texColor), fogFactor);
    FragColor = vec4(fogTexColor, texColor.a);  
} 
