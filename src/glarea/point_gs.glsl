#version 330
#define SCALE 100
#define M_PI 3.14159265

#define ROUND_POINT 1
#define TRIANGLE_POINT 2
#define SQUARE_POINT 3

layout(points) in;
layout(triangle_strip, max_vertices = 100) out;

in vec4 v_color[];
in float v_size[];
in int v_type[];

out vec4 g_color;

void build_curcle(vec4 pos, float size) {
  float radius = (size/SCALE);
  float angle = M_PI/10;

  vec2 v_0 = vec2(1,0);
  vec2 v_i = v_0;

  for (int i = 0; i < 21; ++i) {
    v_i.x = v_0.x * cos(i * angle) - v_0.y * sin(i * angle);
    v_i.y = v_0.x * sin(i * angle) - v_0.y * cos(i * angle);

    gl_Position = pos;
    EmitVertex();

    gl_Position = pos + radius * vec4(v_i.x, v_i.y, 0, 0); //TODO
    EmitVertex();
  }
  EndPrimitive();
}

void build_triangle(vec4 pos, float size) {
  float delta = size/SCALE;

  gl_Position = pos + vec4(delta, 0, 0, 0);
  EmitVertex();

  gl_Position = pos + vec4(-delta, 0, 0, 0);
  EmitVertex();

  gl_Position = pos + vec4(0, delta, 0, 0);
  EmitVertex();
  
  EndPrimitive();
}

void build_square(vec4 pos, float size) {
  float delta = size/SCALE;

  gl_Position = pos + vec4(delta, delta, 0, 0);
  EmitVertex();

  gl_Position = pos + vec4(delta, -delta, 0, 0);
  EmitVertex();

  gl_Position = pos + vec4(-delta, delta, 0, 0);
  EmitVertex();
  
  gl_Position = pos + vec4(-delta, -delta, 0, 0);
  EmitVertex();

  EndPrimitive();
}

void main() {
  g_color = v_color[0];

  if (v_type[0] == ROUND_POINT) {
    build_curcle(gl_in[0].gl_Position, v_size[0]);
  } else if (v_type[0] == TRIANGLE_POINT) {
    build_triangle(gl_in[0].gl_Position, v_size[0]);
  } else {
    build_square(gl_in[0].gl_Position, v_size[0]);
  }
}
