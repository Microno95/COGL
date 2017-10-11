#version 330 core
uniform mat4 mvp;

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 vCol;
layout(location = 3) in vec2 texCoords;
out vec4 color;
void main() {
    gl_Position = mvp * vec4(vPos, 1.0);
//    gl_PointSize = 10.0;
    color = vec4((vPos + vec3(1.0f)) / 2.0f, 1.0f);
}