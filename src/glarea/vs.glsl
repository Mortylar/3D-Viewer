#version 330

layout(location = 0) in vec4 position;
//layout(location = 1) in vec2 texture;

uniform mat4 mvp;

//out vec2 gl_texture;

void main() {
  gl_Position = mvp * position;
	//out_texture = texture;
}
