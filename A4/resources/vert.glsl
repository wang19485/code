#version 120

uniform mat4 P;
uniform mat4 MV;

attribute vec4 aPos; // in object space
attribute vec3 aNor; // in object space

//varying vec3 color; // Pass to fragment shader
varying vec3 normal;
varying vec3 vertP;

void main()
{
	gl_Position = P * MV * aPos;
    vertP = vec3(MV * aPos);
    normal = vec3(mat3(MV) * aNor);
}
