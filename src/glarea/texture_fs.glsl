#version 330

in vec2 TexCoord;

out vec4 outputColor;

uniform sampler2D s21_sampler;

void main() {
  outputColor = texture(s21_sampler, TexCoord);
  //gl_FragColor = texture(s21_sampler, TexCoord);
}
