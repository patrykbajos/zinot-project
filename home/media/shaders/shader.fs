#version 330 core
in vec3 fragColor;
in vec2 fragUV;
uniform sampler2D tex;

out vec4 outColor;

void main()
{
    outColor = texture(tex, fragUV)* vec4(fragColor, 1.0);
}
