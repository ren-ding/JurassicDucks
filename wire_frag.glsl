#version 120

// Shader that just copies Gouraud color to output,
// standard OpenGL shading without texture maps

void main ()
{
    gl_FragColor = gl_Color;
}

