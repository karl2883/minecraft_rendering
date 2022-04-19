#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aShadeFactor;

uniform mat4 MVP;

out vec2 TexCoord;
out float ShadeFactor;

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
    ShadeFactor = aShadeFactor;
}
