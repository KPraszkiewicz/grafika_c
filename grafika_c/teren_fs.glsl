#version 330
in vec2 texture_coordinates;
uniform sampler2D basic_texture;
out vec4 frag_colour;

void main()
{
 frag_colour = texture(basic_texture, texture_coordinates);
 //frag_colour = vec4(1,1,1,1);
}