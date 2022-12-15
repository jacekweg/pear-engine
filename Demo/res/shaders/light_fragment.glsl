#version 460 core

layout(location = 0) out vec4 color;

in vec2 uv;

uniform vec3 input_color;

void main()
{
	float brightness = max(0.0, 1.0 - pow(dot(uv, uv), 0.25));
	color = vec4(brightness * input_color, 1.0);
}