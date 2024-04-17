#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 texture;
layout(location = 2) in vec3 normal;

uniform mat4 mvp;
uniform vec4 color;
uniform vec4 background_color;
uniform float size;
uniform int type;

out vec4 v_color;
out vec4 v_background_color;
out float v_size;
out int v_type;

void main() {
  gl_Position = mvp * position;
  v_color = color;
  v_background_color = background_color;
  v_size = size;
  v_type = type;
}
