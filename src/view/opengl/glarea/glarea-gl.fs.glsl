#version 330

out vec4 outputColor;

void main() {
  //float lerpVal = gl_FragCoord.y / 500.0f;
  outputColor = vec4(1, 0, 0, 1);
  //outputColor = mix(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f), lerpVal);
}
