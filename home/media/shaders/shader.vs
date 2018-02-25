#version 330 core

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertColor;
layout (location = 2) in vec2 vertUV;

out vec2 fragUV;
out vec3 fragColor; // Output a color to the fragment shader

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * vec4(vertPos, 1.0);
    //gl_Position = vec4(position, 1.0) * gl_ModelViewProjectionMatrix;
    
    fragUV = vertUV;
    fragColor = vertColor;
}
