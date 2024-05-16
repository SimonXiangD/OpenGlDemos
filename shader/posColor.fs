#version 330 core
in vec3 pos;

out vec4 FragColor;

void main() {

    FragColor = vec4(0.5+pos.x,0.5+pos.y,0.5+pos.z,1.0);
}