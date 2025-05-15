#version 330 core

layoout(location = 0) in vec 3 inputVertex;

void main(){

gl_Position = vec4(inputVertex, 1.0);
}