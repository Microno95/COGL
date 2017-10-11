#version 330 core
uniform vec3 lightColor;
uniform vec3 lightPos;
in vec4 color;
in vec3 fragPos;
in vec3 Normal;
layout (location = 0) out vec4 out_color;
void main() {
    float ambientStrength = 0.1f;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (pow(diff, 16) * lightColor + diff)/ (dot(lightDir, lightDir) + 1);
    vec3 result = (ambientStrength * color.rgb) + diffuse * color.rgb;
    out_color = vec4(result, color.a);
}