#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 LIGHT_COLOR;  
uniform vec3 LIGHT_POS; 
uniform vec3 CAMERA_POS;

uniform float AMBIENT_LIGHT_STRENGHT;

uniform sampler2D TEXTURE;

void main() {
    vec3 ambient = AMBIENT_LIGHT_STRENGHT * LIGHT_COLOR;

	vec4 colorBeforeLight = texture(TEXTURE, TexCoord) * vec4(1.0, 1.0, 1.0, 1.0) ;
	FragColor = vec4(ambient, 1.0) * colorBeforeLight;
}
