#version 460 core

layout(location = 0) in vec2 vertex;
layout(location = 1) in vec2 input_uv;

out vec2 uv;

uniform mat4 transform;
uniform mat4 view_projection;

void main()
{
	gl_Position = view_projection * transform * vec4(vertex, 0, 1);
	uv = input_uv;
}