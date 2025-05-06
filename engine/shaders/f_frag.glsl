#version 410 core

uniform float time;

in vec3 v_vertexColors;
out vec4 fragColor;

void main(){
    float t = time;
    t /= 75.0;
    t = mod(t, 1.0) + 0.5;

    vec3 newColor = t - v_vertexColors;

    fragColor = vec4(newColor, 1.0);
};