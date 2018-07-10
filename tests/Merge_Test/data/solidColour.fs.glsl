#version 400 core
in vec4 color;
out vec4 out_color;
void main() {
    if (gl_FrontFacing) {
		out_color = color;
	}
	else {
		out_color = vec4(0.0f);
	}

}