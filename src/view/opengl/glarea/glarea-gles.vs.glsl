attribute vec4 position;

uniform mat4 mvp;

void main() {
  gl_Position = mvp * gl_Vertex; //position;
  gl_PointSize = 5.0;
}
