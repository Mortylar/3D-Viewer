#version 330

#define SCALE 500;
#define STRAIGHT_LINE_TYPE 1
#define DOTTED_LINE_TYPE 2

layout(lines) in;
layout (triangle_strip, max_vertices = 100) out;

in vec4 v_color[];
in vec4 v_background_color[];
in float v_size[];
in int v_type[];

out vec4 g_color;

vec3 GetNormal(vec3 dir1, vec3 dir2) {
  return normalize(cross(dir1, dir2));
}


void DrawStraightLine(vec4 pos1, vec4 pos2, float size) {
  size /= SCALE;

  vec3 normal = GetNormal(vec3((pos2 - pos1).xyz), vec3(0,0,1));
  
  gl_Position = pos1 + vec4(size*normal, 0);
  EmitVertex();

  gl_Position = pos1 - vec4(size*normal, 0);
  EmitVertex();

  gl_Position = pos2 + vec4(size*normal, 0);
  EmitVertex();

  gl_Position = pos2 - vec4(size*normal, 0);
  EmitVertex();
}

void DrawDottedLine(vec4 pos1, vec4 pos2, float size) {
  size /= SCALE;

  vec4 line = pos2 - pos1;
  vec3 normal = GetNormal(vec3(line.xyz), vec3(0,0,1));
 
  vec4 right_start = pos1 + vec4(size*normal, 0);
  vec4 left_start = pos1 - vec4(size*normal, 0);

  vec4 fragment_color = v_color[0];
  for (float i = 0.0; i < 1.0; i+=0.04) {
    g_color = fragment_color;
    gl_Position = right_start + i*line;
    EmitVertex();
    
    g_color = fragment_color;
    gl_Position = right_start + (i + 0.02f)*line;
    EmitVertex();

    g_color = fragment_color;
    gl_Position = left_start + i*line;
    EmitVertex();

    g_color = fragment_color;
    gl_Position = left_start + (i + 0.02f)*line;
    EmitVertex();
    
    EndPrimitive();
    fragment_color = (fragment_color == v_color[0]) ? (v_background_color[0]) : (v_color[0]); 
  }
}


void main() {
  if (v_type[0] == STRAIGHT_LINE_TYPE) {
    g_color = v_color[0];
    DrawStraightLine(gl_in[0].gl_Position, gl_in[1].gl_Position, v_size[0]);
  } else {
    DrawDottedLine(gl_in[0].gl_Position, gl_in[1].gl_Position, v_size[0]);
  }
}
