#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec4 vertex; // <vec2 pos, vec2 tex>

out vec4 color;
out vec2 TexCoords;
uniform float offset;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    color = vec4(aColor, 1.0);
    TexCoords = vertex.zw;
};
