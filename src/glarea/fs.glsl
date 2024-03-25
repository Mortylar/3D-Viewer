#version 330

in vec4 u_color;
out vec4 outputColor;

//uniform sampler2D gSampler;

void main() {
  outputColor = u_color;
	//outputColor = texture2D(gSampler, glTexture.st);
}
