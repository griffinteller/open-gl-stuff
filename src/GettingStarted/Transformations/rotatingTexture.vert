#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 uv;

out vec3 vertColor;
out vec2 vertUv;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(pos, 1.0);
    vertColor = col;
    vertUv = uv;
}