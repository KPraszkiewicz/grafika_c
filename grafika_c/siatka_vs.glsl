#version 430
in vec3 pozycja; // position of the vertices
in vec3 v_bc; // barycentric coordinate inside the triangle

out vec3 v_barycentric; // barycentric coordinate inside the triangle

//uniform mat4 t_mvp; // modeview-projection matrix

void main()
{
    //gl_Position = t_mvp * vec4(pozycja,1);
    gl_Position = vec4(pozycja,1);
    v_barycentric = v_bc; // just pass it on
}