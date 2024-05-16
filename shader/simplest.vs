#version 330 core
layout(location=0) in vec3 vecPos;

out vec3 pos;

void main() {
    pos = vecPos;
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}