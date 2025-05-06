#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ProjectionMatrix;

out vec3 v_vertexColors;
out vec2 TexCoords;

void main(){
    v_vertexColors = color;
    TexCoords = position.xy;

    vec4 newPos = u_ProjectionMatrix * u_ModelMatrix * vec4(position, 1.0);

    gl_Position = newPos;
};