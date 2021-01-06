#version 430
in vec3 v_barycentric; // barycentric coordinate inside the triangle
//uniform float f_thickness; // thickness of the rendered lines
out vec4 kolor;

void main()
{
    float f_thickness = 0.01;
    float f_closest_edge = min(v_barycentric.x,
        min(v_barycentric.y, v_barycentric.z)); // see to which edge this pixel is the closest
    float f_width = fwidth(f_closest_edge); // calculate derivative (divide f_thickness by this to have the line width constant in screen-space)
    float f_alpha = smoothstep(f_thickness, f_thickness + f_width, f_closest_edge); // calculate alpha
    kolor = vec4(vec3(1.0), f_alpha);
}