#version 120
// Texture map shader

uniform sampler2D gTex;

void main ()
{
    gl_FragColor = texture2D(gTex, gl_TexCoord[0].st);
    if (gl_FragColor.a == 0.0)
        discard;
    // HACK because QImage loader doesn't handle transparency
	if (gl_FragColor.r == 0 && gl_FragColor.g == 0 && gl_FragColor.b == 0)
        discard;
}
