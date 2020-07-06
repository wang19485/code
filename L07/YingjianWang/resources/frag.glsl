#version 120

uniform vec3 lightPos;
//uniform vec3 lightPos2;
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float s;
uniform float intensity1;
uniform mat4 MV;
//uniform float intensity2;

//varying vec3 color; // passed from the vertex shader
varying vec3 normal;
varying vec3 vertP;

void main()
{
    vec3 n = normalize(normal);
    //1
    vec3 halfvert = normalize(normalize(mat3(MV)*lightPos - vertP) + normalize(-vertP));
    vec4 diff_color = vec4(kd,1.0) * max(0.0,dot(normalize(mat3(MV)*lightPos - vertP), n));
    vec4 spec_color = vec4(ks,1.0) * pow(max(0.0,dot(halfvert, n)),s);
    //2
    
    gl_FragColor = intensity1 * (vec4(ka,1.0) + diff_color + spec_color);
}
