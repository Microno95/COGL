#version 410 core
uniform mat4 proj;
uniform mat4 view;

struct vertex {
    vec3 pos;
    vec3 normal;
    vec4 colour;
    vec2 uv;
};

layout(location = 0) in vec3 _pos;
layout(location = 1) in vec3 _normal;
layout(location = 2) in vec4 _colour;
layout(location = 3) in vec2 _uv;

vertex vertex_in = vertex(_pos, _normal, _colour, _uv);

layout(location = 4) in mat4 model;

out vec4 color;
void main() {
    gl_Position = proj * view * model * vec4(vertex_in.pos, 1.0);
    gl_PointSize = 25.0;
    color = vec4(1.0f);
}