#version 330 core

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertNorm;
layout (location = 2) in vec2 vertUv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec4 fragColor;
out vec3 fragNorm;
out vec2 fragUv;

void main()
{
    mat4 mvp = proj * view * model;

    gl_Position = mvp * vec4(vertPos, 1.0);

    fragColor = vec4(0.8f, 0.8f, 0.8f, 1.0f);
    fragNorm = (mvp * vec4(vertNorm, 0.0f)).xyz;
    fragUv = vertUv;
}
