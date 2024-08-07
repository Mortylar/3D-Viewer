#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 texture;
layout(location = 2) in vec3 normal;

uniform mat4 mvp;
uniform vec4 color;

out vec4 u_color;
out vec2 TexCoord;

void main() {
  gl_Position = mvp * position;
  TexCoord = vec2(texture.x, texture.z);
  u_color = color;
}
