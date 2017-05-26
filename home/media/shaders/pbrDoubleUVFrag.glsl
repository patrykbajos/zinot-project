#version 330 core

in vec3 fragPos;
in vec3 fragNorm;
in vec4 fragTan;
in vec2 fragUv1;
in vec2 fragUv2;

uniform sampler2D texDiffuse;
uniform sampler2D texAO;

out vec3 posWorld;
out vec3 normalWorld;
out vec4 tanWorld;

void main()
{
    outColor = fragColor * texture2D(texDiff, fragUv) * dot(vec3(0.0f, 0.0f, -1.0f), fragNorm);
}
