#version 330 core

// Uniform inputs
uniform mat4 worldViewMatrix;
uniform sampler2D normalMap;

in Data
{
    vec3 positionViewspace;
    vec3 normalViewspace;
    vec3 tangentLocalspace;
    vec3 bitangentLocalspace;
    vec3 normalLocalspace;
    vec2 texCoords;
} FSIn;

out vec4 outColor;
float ambientTerm = 0.5;

void main(void)
{
    vec3 L = -normalize(FSIn.positionViewspace);
    vec3 N = normalize(FSIn.normalViewspace);
    vec3 albedo = vec3(1, 0, 0);
    float kD = max(0.0, dot(L,N));
    //outColor.rgb = albedo * kD;
    outColor.rgb += albedo * ambientTerm;
    outColor.a = 1.0;

    // Gamma Correction
    outColor.rgb = pow(outColor.rgb, vec3(1.0/2.4));

    // Tangent to local (TBN) matrix
    vec3 T = normalize(FSIn.tangentLocalspace);
    vec3 B = normalize(FSIn.bitangentLocalspace);
    vec3 N = normalize(FSIn.normalLocalspace);
    mat3 TBN = mat3(T, B, N);

    // Convert normal from tangent space to local space and view space
    vec3 tangentSpaceNormal = texture(normalMap, FSIn.texCoords).xyz * 2.0 - vec3(1.0);
    vec3 localSpaceNormal = TBN * tangentSpaceNormal;
    vec3 viewSpaceNormal = normalize(worldViewMatrix * vec4(localSpaceNormal, 0.0)).xyz;

}
