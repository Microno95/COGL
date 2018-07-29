#version 410 core
uniform mat4 vp;

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
    gl_Position = vp * model * vec4(vertex_in.pos, 1.0);
    float angle = atan(vertex_in.pos.x, vertex_in.pos.z);
    color = vec4(1.0f + 0.5f * cos(angle) + vertex_in.pos.x, 1.0f + 0.5f * sin(angle) + vertex_in.pos.y, 0.5f, 0.5f);
    color = normalize(color);
}