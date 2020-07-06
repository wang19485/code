#version 120

uniform vec3 lightPos;
uniform vec3 lightPos2;
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float s;
uniform float intensity1;
uniform float intensity2;

//varying vec3 color; // passed from the vertex shader
varying vec3 normal;
varying vec3 vertP;

void main()
{
    vec3 n = normalize(normal);
    //1
    vec3 black = vec3(0.0f,0.0f,0.0f);
    vec3 ka_white = vec3(1.0f,1.0f,1.0f);
    
    vec3 halfvert = normalize(normalize(lightPos - vertP) + normalize(-vertP));
    vec4 diff_color = vec4(kd,1.0) * max(0.0,dot(normalize(lightPos - vertP), n));
    vec4 spec_color = vec4(ks,1.0) * pow(max(0.0,dot(halfvert, n)),s);
    if (max(0.0,dot(normalize(-vertP), n)) < 0.35) {
        diff_color = vec4(black,1.0) * max(0.0,dot(normalize(lightPos - vertP), n));
    }
    //2
    vec3 halfvert2 = normalize(normalize(lightPos2 - vertP) + normalize(-vertP));
    vec4 diff_color2 = vec4(kd,1.0) * max(0.0,dot(normalize(lightPos2 - vertP), n));
    vec4 spec_color2 = vec4(ks,1.0) * pow(max(0.0,dot(halfvert2, n)),s);
    if (max(0.0,dot(normalize(-vertP), n)) < 0.35) {
        diff_color2 = vec4(black,1.0) * max(0.0,dot(normalize(lightPos2 - vertP), n));
    }
    
    if (max(0.0,dot(normalize(-vertP), n)) < 0.35) {
        gl_FragColor = intensity1 * (vec4(ka,1.0) + diff_color + spec_color) + intensity2 * (vec4(ka,1.0) + diff_color2 + spec_color2);
    }else{
        gl_FragColor = intensity1 * (vec4(ka_white,1.0) + diff_color) + intensity2 * (vec4(ka_white,1.0) + diff_color2);
    }
    
}
