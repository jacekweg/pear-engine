#version 460 core

layout(location = 0) in vec3 vertex;

uniform mat4 transform;
uniform mat4 view_projection;
uniform vec2 input_light_position;

void main()
{
	vec2 shadow_position = (view_projection * transform * vec4(vertex.xy, 0.0, 1.0)).xy;
	vec2 light_position = (view_projection * vec4(input_light_position, 0.0, 1.0)).xy;

	gl_Position = vec4(shadow_position - vertex.z * light_position, 0.0, 1.0 - vertex.z);
}