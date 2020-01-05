#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D Texture0;
uniform sampler2D Texture1;

void main()
{
    //color = mix(texture(Texture0, TexCoord),texture(Texture1, TexCoord),0.4);
	//color = vec4(ourColor, 1.0);
	color = texture(Texture0, TexCoord) * vec4(ourColor, 1.0);
}
