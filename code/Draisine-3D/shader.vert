#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;
out vec3 Normal;

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;
uniform mat4 MVP;

void main() {
    gl_Position = PROJECTION *  VIEW  * MODEL * vec4(position, 1.0f);
    TexCoord = texCoord;
    Normal = normal;
}
