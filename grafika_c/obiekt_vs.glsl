#version 330
layout (location = 0) in vec3 pozycja;
layout (location = 1) in vec4 kolor_rgba;
uniform mat4 MVP;

out vec4 kolor;

void main()
{
	kolor = kolor_rgba;
	gl_Position = MVP * vec4(pozycja,1);
}