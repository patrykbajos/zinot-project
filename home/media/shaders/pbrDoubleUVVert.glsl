#version 330 core

in vec3 vertPos;
in vec3 vertNorm;
in vec4 vertTan;
in vec2 vertUv1;
in vec2 vertUv2;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

uniform float metalness;
uniform float roughness;
uniform sampler2D texDiffuse;
uniform sampler2D texAO;

out vec3 fragPos;
out vec3 fragNorm;
out vec4 fragTan;
out vec2 fragUv1;
out vec2 fragUv2;

void main()
{
    mat4 mvp = projMat * viewMat * modelMat;

    gl_Position = mvp * vec4(vertPos, 1.0f);

    fragColor = vec4(0.8f, 0.8f, 0.8f, 1.0f);
    fragNorm = (mvp * vec4(vertNorm, 0.0f)).xyz;
    fragUv = vertUv;
}
