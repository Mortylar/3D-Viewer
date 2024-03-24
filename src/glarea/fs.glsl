#version 330

//in vec2 gl_texture
out vec4 outputColor;

//uniform sampler2D gSampler;

void main() {
  outputColor = vec4(1, 0, 1, 1);
	//outputColor = texture2D(gSampler, glTexture.st);
}
