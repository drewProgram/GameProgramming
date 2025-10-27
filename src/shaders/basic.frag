
#version 460 core

in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 color;
uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    // mix combines textures
    // 0.2 returns 80% of the first input color and 20% of the second
    FragColor = mix(texture(tex1, TexCoord), texture(tex2, TexCoord), 0.2);
}