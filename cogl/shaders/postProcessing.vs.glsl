#version 410 core

layout(location=0)in vec3 v_coord;
out vec2 f_texcoord;

void main() {
  gl_Position = vec4(v_coord, 1.0f);
  f_texcoord = (v_coord.xy + vec2(1.0f))/2.0f;
}