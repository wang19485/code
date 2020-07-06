#version 120

uniform mat4 P;
attribute vec3 vertPos;

void main()
{
	gl_Position = P * vec4(vertPos, 1.0);
}
