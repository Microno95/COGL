#version 330 core

const float offset = 0.5 / 300;
uniform sampler2D fbo_texture;
uniform float time;
uniform float exposure;
in vec2 f_texcoord;
out vec4 color;

void main()
{
	vec2 texcoord = f_texcoord;
	// texcoord.x += sin(texcoord.y * 4*2*3.14159 + time) / 100;
    vec2 offsets[9] = vec2[](
        vec2(-offset, offset),  // top-left
        vec2(0.0f,    offset),  // top-center
        vec2(offset,  offset),  // top-right
        vec2(-offset, 0.0f),    // center-left
        vec2(0.0f,    0.0f),    // center-center
        vec2(offset,  0.0f),    // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f,    -offset), // bottom-center
        vec2(offset,  -offset)  // bottom-right
);

    float kernel[9] = float[](
        -0.25, -1, -0.25,
        -1,  5, -1,
        -0.25, -1, -0.25
    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(fbo_texture, texcoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++) col += sampleTex[i] * kernel[i];

	const float gamma = 2.2;
	vec3 hdrColor = col.rgb;

	// Exposure tone mapping
	vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
	// Gamma correction
	mapped = pow(mapped, vec3(1.0 / gamma));

	color = vec4(mapped, 1.0);
}