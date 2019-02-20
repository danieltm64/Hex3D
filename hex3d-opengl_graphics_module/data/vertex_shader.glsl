#version 300 es

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
out vec4 Color;

uniform mat4 WVP;

void main()
{
    gl_Position = WVP * vec4(position.xyz, 1.0);
    Color = color;
}
