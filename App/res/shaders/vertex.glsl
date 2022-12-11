#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 input_text_coord;

uniform mat4 view_projection;
uniform mat4 transform;

out vec2 text_coord;

void main()
{
	text_coord = input_text_coord;
	gl_Position = view_projection * transform * vec4(position, 1.0);
}