#version 330 core
uniform mat4 proj;
uniform mat4 view;

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 vCol;
layout(location = 3) in mat4 modelMatrix;
layout(location = 7) in mat4 normalMatrix;
out vec4 color;
out vec3 fragPos;
out vec3 Normal;
void main() {
    gl_Position = proj * view * modelMatrix * vec4(vPos, 1.0);
    gl_PointSize = 7.5;
    color = vCol;
    fragPos = vec3(proj * view * modelMatrix * vec4(vPos, 1.0));
    Normal = normalize(vec3(normalMatrix * vec4(normal, 0.0f)));
}