#version 330 core
layout(location=0) in vec3 vecPos;

out vec3 pos;


uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
    pos = vecPos;
    gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0);
}