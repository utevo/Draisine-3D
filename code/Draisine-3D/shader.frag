#version 330 core
in vec2 TexCoord;
in vec3 Normal;

out vec4 color;

uniform sampler2D TEXTURE;

void main() {
	color = texture(TEXTURE, TexCoord) * vec4(1.0, 1.0, 1.0, 1.0) ;
}
