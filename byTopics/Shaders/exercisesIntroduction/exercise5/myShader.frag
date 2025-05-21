#version 330 core
out vec4 fragColor;

void main(){

  float normalizedCoord = gl_FragCoord.x / float(640);

  float red = normalizedCoord;
  float blue = 1.0 - normalizedCoord;
  float green = 0.0;

  fragColor = vec4(red, green, blue, 1.0);

}
