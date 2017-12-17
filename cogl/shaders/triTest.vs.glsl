#version 400 core
uniform mat4 proj;
uniform mat4 view;

struct vertex {
    vec3 pos;
    vec3 normal;
    vec4 colour;
    vec2 uv;
};

layout(location = 0) in vertex vertex_in;

layout(location = 4) in mat4 model;

out vec4 color;
void main() {
    gl_Position = proj * view * model * vec4(vertex_in.pos, 1.0);
    gl_PointSize = 25.0;
    float angle = atan(gl_Position.x, gl_Position.z);
    color = vec4(1.0f + 0.5f * cos(angle) + gl_Position.x, 1.0f + 0.5f * sin(angle) + gl_Position.y, 0.5f, 0.5f);
    color = normalize(color);
}