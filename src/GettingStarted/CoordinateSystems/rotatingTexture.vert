#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

out vec3 vertColor;
out vec2 vertUv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    vertUv = uv;
}