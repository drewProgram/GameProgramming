#version 460 core
out vec4 FragColor;
in vec3 crazyColor;

void main()
{
    FragColor = vec4(crazyColor, 1.0);
}