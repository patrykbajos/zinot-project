#version 330 core

in vec4 fragColor;
in vec3 fragNorm;
in vec2 fragUv;
uniform sampler2D texDiff;

out vec4 outColor;

void main()
{
    outColor = fragColor * texture2D(texDiff, fragUv);
}
