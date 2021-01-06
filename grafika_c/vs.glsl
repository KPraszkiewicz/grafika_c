#version 430

in vec3 pozycja;
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(pozycja,1);
}