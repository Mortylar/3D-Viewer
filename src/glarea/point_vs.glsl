#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 texture;
layout(location = 2) in vec3 normal;

uniform mat4 mvp;
uniform vec4 color;
uniform float size;

out vec4 v_color;
out float v_size;

void main() {
  gl_Position = mvp * position;
  v_color = color;
  v_size = size;
}
