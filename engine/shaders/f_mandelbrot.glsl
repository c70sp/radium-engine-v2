#version 410 core

out vec4 FragColor;
in vec2 TexCoords; // -1,1

uniform vec2 u_center; // center of view, e.g. 0,0
uniform float u_zoom;
uniform int u_maxIterations;

void main(){
    vec2 c = u_center + TexCoords * u_zoom;

    vec2 z = vec2(0.0);
    int i;
    for(i = 0; i < u_maxIterations; ++i){
        vec2 z_new;
        z_new.x = z.x * z.x - z.y * z.y + c.x;
        z_new.y = 2.0 * z.x * z.y + c.y;

        z = z_new;

        if(dot(z, z) > 4.0) break; // |z|^2 > 4 -> escapes
    }

    float t = float(i) / float(u_maxIterations);
    vec3 color = 0.5 + 0.5*cos(6.2831*(t + vec3(0.6, 0.33, 0.67)));
    FragColor = vec4(color, 1.0);
}