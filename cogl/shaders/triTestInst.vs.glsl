#version 410 core
uniform mat4 view;
uniform mat4 proj;

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

layout(location = 4) in mat4 model;

out vec4 color;

vertex vertex_in = vertex(_pos, _normal, _colour, _uv);

void main() {
    gl_Position = proj * view * model * vec4(vertex_in.pos.xyz, 1.0f);
    color = vec4(1.0f);
}