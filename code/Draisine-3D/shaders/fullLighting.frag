#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 LIGHT_COLOR;  
uniform vec3 LIGHT_POS; 
uniform vec3 CAMERA_POS;

uniform float AMBIENT_LIGHT_STRENGHT;
uniform float DIFFUSE_LIGHT_STRENGHT;
uniform float SPECULAR_LIGHT_STRENGHT;

uniform sampler2D TEXTURE;

void main() {
    // ambient light
    vec3 ambient = AMBIENT_LIGHT_STRENGHT * LIGHT_COLOR;

    // diffuse light
	vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LIGHT_POS - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = DIFFUSE_LIGHT_STRENGHT * diff * LIGHT_COLOR;

    // specular ligth
    vec3 viewDir = normalize(CAMERA_POS - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = SPECULAR_LIGHT_STRENGHT * spec * LIGHT_COLOR; 

    vec3 light = ambient + diffuse + specular;
	vec4 colorBeforeLight = texture(TEXTURE, TexCoord) * vec4(1.0, 1.0, 1.0, 1.0) ;
	FragColor = vec4(light, 1.0) * colorBeforeLight;
}
