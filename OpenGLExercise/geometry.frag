#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedo;
layout (location = 3) out vec3 gSpecular;

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
uniform sampler2D normalMap;
uniform mat4 modelMatrix;

uniform int diffuseEnabled;
uniform int normalEnabled;
uniform int specularEnabled;

uniform float viewPosX;
uniform float viewPosY;
uniform float viewPosZ;

uniform float Lx;
uniform float Ly;
uniform float Lz;

vec3 L = vec3(0, 0, 1);

float SpecStrength = 0.5;

void main()
{

    L = vec3(Lx, Ly, Lz);

    vec3 viewPos = vec3(viewPosX, viewPosY, viewPosZ);

    // store the fragment position vector in the first gbuffer texture
    gPosition = FSIn.positionViewspace;

    if(normalEnabled == 1)
    {
        vec3 T = normalize(FSIn.tangentLocalspace);
        vec3 B = normalize(FSIn.bitangentLocalspace);
        vec3 N = normalize(FSIn.normalLocalspace);

        mat3 TBN = mat3(T, B, N);
        vec3 normalTangent = texture(normalMap, FSIn.texCoords).rgb;
        normalTangent = normalize(normalTangent * 2.0 - 1.0);

        vec3 normalLocal = normalize(TBN * normalTangent);
        vec3 normalView = normalize(modelMatrix * vec4(normalLocal, 0.0)).xyz;

        // also store the per-fragment normals into the gbuffer
        gNormal = normalView;

    }
    else
    {
        // also store the per-fragment normals into the gbuffer
        gNormal = normalize(FSIn.normalViewspace);
        //gNormal = vec3(1.0, normalEnabled, 0.0);
    }

    if(specularEnabled == 1)
    {
        vec3 fragPos = vec3(modelMatrix * vec4(gPosition, 1.0));

        vec3 V = normalize(viewPos - fragPos);
        vec3 R = reflect(-L, gNormal);
        float spec = pow(max(dot(V, R), 0.0), 32);
        vec3 specular = vec3(SpecStrength * spec);
        gSpecular = specular;
    }
    else
    {
        gSpecular = vec3(0);
    }
    if(diffuseEnabled == 1)
    {
        gAlbedo.rgb = texture(diffuseTex, FSIn.texCoords).rgb;
    }
    else
    {
        // and the diffuse per-fragment color
        gAlbedo.rgb = vec3(1.0, 0.0, 0.0);
    }
}
