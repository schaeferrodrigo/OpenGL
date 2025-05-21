#version 330 core
out vec4 FragColor;
uniform float time;

void main() {
    FragColor = vec4(sin(time)*0.5 + 0.5, 0.5, 0.5, 1.0);
}