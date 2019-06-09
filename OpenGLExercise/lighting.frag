#version 330 core

in Data
{
    vec2 TexCoords;
} FSIn;

out vec4 FragColor;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D gSpecular;

uniform float Lx;
uniform float Ly;
uniform float Lz;

float ambientTerm = 0.05;
vec3 L = vec3(0,0,1);
vec3 lightColor = vec3(1,1,1);

float dlIntensity = 0.75f;

vec3 plPos = vec3(0, 0, 0);
float plRadius = 15f;
vec3 plColor = vec3(1, 0, 0);

float plIntensity = 1.5f;

void main(void)
{

    L = vec3(Lx, Ly, Lz);

    vec3 fragPos = texture(gPosition, FSIn.TexCoords).rgb;
    vec3 fragNormal = texture(gNormal, FSIn.TexCoords).rgb;
    vec3 fragDiffuse = texture(gAlbedo, FSIn.TexCoords).rgb;
    vec3 fragSpecular = texture(gSpecular, FSIn.TexCoords).rgb;

    vec3 ambient = ambientTerm * fragDiffuse;
    vec3 diffuse = max(dot(fragNormal, L), 0.0) * lightColor * fragDiffuse;
    vec3 specular = lightColor * fragSpecular.x * fragDiffuse;

    vec3 directionalLight = ambient + specular + diffuse;

    vec3 pL = normalize(plPos - fragPos);
    vec3 pl_amb = ambientTerm * fragDiffuse;
    vec3 pl_diff = max(dot(fragNormal, pL), 0.0) * plColor * fragDiffuse;
    vec3 pl_spec = plColor * fragSpecular.x * fragDiffuse;

    float att = 1.0 / length(plPos - fragPos);
    att *= max(1 - length(plPos - fragPos) / plRadius, 0.0);

    vec3 pointLight = pl_amb + pl_diff + pl_spec;
    pointLight *= att;

    FragColor.rgb = directionalLight * dlIntensity + pointLight * plIntensity;

    //vec3 N = normalize(fragNormal);
    //float kD = max(0.0, dot(L,N));
    //FragColor.rgb = fragDiffuse*kD;
    //FragColor.a = 1.0;

    //GammaCorrection
    FragColor.rgb = pow(FragColor.rgb, vec3(1.0/2.4));


    //FragColor.rgb = fragDiffuse;
}
