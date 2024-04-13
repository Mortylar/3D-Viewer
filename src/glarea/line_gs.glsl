#version 330

#define SCALE 500;

layout(lines) in;
layout (triangle_strip, max_vertices = 100) out;

in vec4 v_color[];
in float v_size[];

out vec4 g_color;

void DrawSquare(vec4 pos1, vec4 pos2, float size) {
  size /= SCALE;

  vec3 direction = vec3((pos2 - pos1).xyz);
  vec3 z_direction = vec3(0,0,1);

  vec3 normal = normalize(cross(direction, z_direction)); //vec2(pos2.y - pos1.y, pos2.x - pos1.x);
  //normal = normalize(normal);
  
  gl_Position = pos1 + vec4(size*normal, 0);
  EmitVertex();

  gl_Position = pos1 - vec4(size*normal, 0);
  EmitVertex();

  gl_Position = pos2 + vec4(size*normal, 0);
  EmitVertex();

  gl_Position = pos2 - vec4(size*normal, 0);
  EmitVertex();
}



void main() {
  g_color = v_color[0];
  DrawSquare(gl_in[0].gl_Position, gl_in[1].gl_Position, v_size[0]);

  //int length = gl_in.length();
  //for (int i = 0; i < length; ++i) {
  //  gl_Position = gl_in[i].gl_Position;
  //  EmitVertex();
  //}
  //EndPrimitive();
}
