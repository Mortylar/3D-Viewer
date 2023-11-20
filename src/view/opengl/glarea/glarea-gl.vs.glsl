#version 450

layout(location = 0) in vec4 position;
uniform mat4 mvp;

void main() {
  gl_Position = mvp * position;
  //gl_Position.xyzw = position;
  //gl_Position.w = 1.0;
}
