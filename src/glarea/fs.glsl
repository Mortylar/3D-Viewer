#version 330

in vec4 u_color;
in vec2 TexCoord;

out vec4 outputColor;

uniform sampler2D s21_sampler;

void main() {
  //outputColor = u_color;
  outputColor = texture(s21_sampler, TexCoord);// * vec4(0,1,0,1);
  //gl_LineWidth = 10.0f;
  //gl_FragColor = vec4(gl_FragCoord.zxy / 500.0, 1.0);
	//outputColor = texture2D(gSampler, glTexture.st);
}
