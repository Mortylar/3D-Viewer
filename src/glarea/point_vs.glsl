#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 texture;
layout(location = 2) in vec3 normal;

uniform mat4 mvp;
uniform vec4 color;

out vec4 u_color;

void main() {
  gl_Position = mvp * position;
  u_color = color;
}
