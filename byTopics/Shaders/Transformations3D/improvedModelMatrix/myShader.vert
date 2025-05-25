#version 330 core
layout(location = 0 ) in vec3 position;

uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;
uniform mat4 scaleMatrix;


void main(){
	
	mat4 model = translationMatrix * rotationMatrix * scaleMatrix;
	gl_Position = model*vec4(position, 1.0);

}