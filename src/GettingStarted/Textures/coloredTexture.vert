#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 uv;

out vec3 vertColor;
out vec2 vertUv;

void main()
{
    gl_Position = vec4(pos, 1.0);
    vertColor = col;
    vertUv = vec2(uv.x, 1 - uv.y);
}