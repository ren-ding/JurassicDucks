#version 120
// Shader that just copies input color

void main ()
{
    vec3 normal, lightDir;
    vec4 ambient, diffuse, specular;
    float NdotL, NdotHV;

    // Standard transform
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    // Eye space surface normal
    normal = normalize(gl_NormalMatrix * gl_Normal);

    // Direction to light source
    lightDir = normalize(vec3(gl_LightSource[0].position));

    // Ambient
    ambient = gl_LightModel.ambient * gl_FrontMaterial.ambient;

    // Diffuse
    NdotL = max(dot(normal, lightDir), 0.0);
    diffuse = (gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse) * NdotL;

    // Specular
    if (NdotL > 0.0) {
        // normalize the half-vector, then compute the
        // cosine (dot product) with the normal
        NdotHV = max(dot(normal, gl_LightSource[0].halfVector.xyz), 0.0);
        specular = gl_FrontMaterial.specular * gl_LightSource[0].specular;
        // And multiply by shininess
        specular = specular * pow(NdotHV, gl_FrontMaterial.shininess);
    }
    // Final
    gl_FrontColor = ambient + diffuse + specular;

    // Pass texture coords without change
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_TexCoord[1] = gl_MultiTexCoord1;
    gl_TexCoord[2] = gl_MultiTexCoord2;
    gl_TexCoord[3] = gl_MultiTexCoord3;
}
