#version 120
// Standard Gouraud shader

void main ()
{
    // Standard transform
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    // TODO: lighting
    gl_FrontColor = gl_Color;

    // Pass texture coords without change
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_TexCoord[1] = gl_MultiTexCoord1;
    gl_TexCoord[2] = gl_MultiTexCoord2;
    gl_TexCoord[3] = gl_MultiTexCoord3;
}
