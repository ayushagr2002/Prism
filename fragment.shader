#version 330 core
out vec4 FragColor;
uniform vec4 ourCol;
void main()
{
	FragColor = ourCol;
}