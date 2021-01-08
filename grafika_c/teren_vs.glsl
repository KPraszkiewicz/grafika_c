#version 330
layout (location = 0) in vec3 pozycja;
layout (location = 1) in vec2 uv_tex;
uniform mat4 MVP;

out vec2 texture_coordinates;

void main()
{
	texture_coordinates = uv_tex;
	gl_Position = MVP * vec4(pozycja,1);
}