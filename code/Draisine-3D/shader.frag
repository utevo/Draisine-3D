#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 LIGHT_COLOR;  
uniform vec3 LIGHT_POS; 
uniform vec3 CAMERA_POS; 

uniform sampler2D TEXTURE;

void main() {
	FragColor = texture(TEXTURE, TexCoord) * vec4(1.0, 1.0, 1.0, 1.0) ;
}
