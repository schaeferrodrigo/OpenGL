#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

//out vec4 fColor;

void main(){

    for(int i= 0; i< gl_in.length(); i++){

        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();

}