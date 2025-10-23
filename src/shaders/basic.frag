
#version 460 core

in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 color;
uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, TexCoord);
    // FragColor = vec4(color, 1.0);
}