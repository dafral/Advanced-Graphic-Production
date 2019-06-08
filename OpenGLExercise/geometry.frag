#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedo;

in Data
{
    vec3 positionViewspace;
    vec3 normalViewspace;
    vec3 tangentLocalspace;
    vec3 bitangentLocalspace;
    vec3 normalLocalspace;
    vec2 texCoords;
} FSIn;

uniform sampler2D diffuseTex;

void main()
{
    // store the fragment position vector in the first gbuffer texture
    gPosition = FSIn.positionViewspace;
    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(FSIn.normalViewspace);
    // and the diffuse per-fragment color
    gAlbedo.rgb = texture(diffuseTex, FSIn.texCoords).rgb;
}
