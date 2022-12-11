#version 460 core

layout(location = 0) out vec4 color;

in vec2 text_coord;

uniform vec4 square_color;
uniform float tiling_factor;
uniform sampler2D texture_data;

void main()
{
	color = texture(texture_data, text_coord * tiling_factor) * square_color;
}