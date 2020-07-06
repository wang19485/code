#include <iostream>
#include <string>
#include <algorithm>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Image.h"
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
#include <math.h>

#define EPSILON 0.000001
#define CROSS(dest,v1,v2) \
dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest,v1,v2) \
dest[0]=v1[0]-v2[0]; \
dest[1]=v1[1]-v2[1]; \
dest[2]=v1[2]-v2[2];

using namespace std;
using namespace glm;

int intersect_triangle3(double orig[3], double dir[3],
                        double vert0[3], double vert1[3], double vert2[3],
                        double *t, double *u, double *v)
{
    double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
    double det,inv_det;
    
    /* find vectors for two edges sharing vert0 */
    SUB(edge1, vert1, vert0);
    SUB(edge2, vert2, vert0);
    
    /* begin calculating determinant - also used to calculate U parameter */
    CROSS(pvec, dir, edge2);
    
    /* if determinant is near zero, ray lies in plane of triangle */
    det = DOT(edge1, pvec);
    
    /* calculate distance from vert0 to ray origin */
    SUB(tvec, orig, vert0);
    inv_det = 1.0 / det;
    
    CROSS(qvec, tvec, edge1);
    
    if (det > EPSILON)
    {
        *u = DOT(tvec, pvec);
        if (*u < 0.0 || *u > det)
            return 0;
        
        /* calculate V parameter and test bounds */
        *v = DOT(dir, qvec);
        if (*v < 0.0 || *u + *v > det)
            return 0;
        
    }
    else if(det < -EPSILON)
    {
        /* calculate U parameter and test bounds */
        *u = DOT(tvec, pvec);
        if (*u > 0.0 || *u < det)
            return 0;
        
        /* calculate V parameter and test bounds */
        *v = DOT(dir, qvec) ;
        if (*v > 0.0 || *u + *v < det)
            return 0;
    }
    else return 0;  /* ray is parallell to the plane of the triangle */
    
    *t = DOT(edge2, qvec) * inv_det;
    (*u) *= inv_det;
    (*v) *= inv_det;
    
    return 1;
}


float maxm(float a,float b){
    if (a > b) {
        return a;
    }else{
        return b;
    }
}

class Color{
public:
    // ***************** Scene 1 *********************
    vec3 light = vec3(-2.0f,1.0f,1.0f);
    vec3 camara = vec3(0.0f,0.0f,5.0f);
    //Red
    vec3 center_red = vec3(-0.5f,-1.0f,1.0f);
    vec3 ka_red = vec3(0.1f,0.1f,0.1f);
    vec3 kd_red = vec3(1.0f,0.0f,0.0f);
    vec3 ks_red = vec3(1.0f,1.0f,0.5f);
    vec3 scale_red = vec3(1.0f,1.0f,1.0f);
    float s_red = 100.0f;
    
    //Green
    vec3 center_green = vec3(0.5f,-1.0f,-1.0f);
    vec3 ka_green = vec3(0.1f,0.1f,0.1f);
    vec3 kd_green = vec3(0.0f,1.0f,0.0f);
    vec3 ks_green = vec3(1.0f,1.0f,0.5f);
    vec3 scale_green = vec3(1.0f,1.0f,1.0f);
    float s_green = 100.0f;
    //Blue
    vec3 center_blue = vec3(0.0f,1.0f,0.0f);
    vec3 ka_blue = vec3(0.1f,0.1f,0.1f);
    vec3 kd_blue = vec3(0.0f,0.0f,1.0f);
    vec3 ks_blue = vec3(1.0f,1.0f,0.5f);
    vec3 scale_blue = vec3(1.0f,1.0f,1.0f);
    
    float s_blue = 100.0f;
    
    vec3 normalc;
    vec3 x_ray_sphere1;
    vec3 x_ray_sphere2;
    vec3 x_ray;
    vec3 rayorigin;
    vec4 gl_FragColor;
    
    // ***************** Scene 2 ************************
    vec3 light1 = vec3(1.0f,2.0f,2.0f);
    vec3 light2 = vec3(-1.0f,2.0f,-1.0f);
    float intensity1 = 0.5f;
    float intensity2 = 0.5f;
    
    vec3 ellip_center = vec3(0.5f,0.0f,0.5f);
    vec3 ellip_scale = vec3(0.5f,0.6f,0.2f);
    vec3 ellip_ka = vec3(0.1f,0.1f,0.1f);
    vec3 ellip_kd = vec3(1.0f,0.0f,0.0f);
    vec3 ellip_ks = vec3(1.0f,1.0f,0.5f);
    float ellip_s = 100.0f;
    
    vec3 sphere_center = vec3(-0.5f,0.0f,-0.5f);
    vec3 sphere_scale = vec3(1.0f,1.0f,1.0f);
    vec3 sphere_ka = vec3(0.1f,0.1f,0.1f);
    vec3 sphere_kd = vec3(0.0f,1.0f,0.0f);
    vec3 sphere_ks = vec3(1.0f,1.0f,0.5f);
    float sphere_s = 100.0f;
    
    vec3 plane_center = vec3(0.0f,-1.0f,0.0f);
    vec3 plane_ka = vec3(0.1f,0.1f,0.1f);
    vec3 plane_kd = vec3(1.0f,1.0f,1.0f);
    vec3 plane_ks = vec3(0.0f,0.0f,0.0f);
    float plane_s = 0.0f;
    
    // ***************** Scene 3 ********************
    vec3 light11 = vec3(-1.0f,2.0f,1.0f);
    vec3 light22 = vec3(0.5f,-0.5f,0.0f);
    
    vec3 sph_red_center = vec3(0.5f,-0.7f,0.5f);
    vec3 sph_red_scale = vec3(0.3f,0.3f,0.3f);
    vec3 sph_red_kd = vec3(1.0f,0.0f,0.0f);
    vec3 sph_red_ks = vec3(1.0f,1.0f,0.5f);
    vec3 sph_red_ka = vec3(0.1f,0.1f,0.1f);
    float sph_red_s = 100.0f;
    
    vec3 sph_blue_center = vec3(1.0f,-0.7f,0.0f);
    vec3 sph_blue_scale = vec3(0.3f,0.3f,0.3f);
    vec3 sph_blue_kd = vec3(0.0f,0.0f,1.0f);
    vec3 sph_blue_ks = vec3(1.0f,1.0f,0.5f);
    vec3 sph_blue_ka = vec3(0.1f,0.1f,0.1f);
    float sph_blue_s = 100.0f;
    
    vec3 floor_center = vec3(0.0f,-1.0f,0.0f);
    vec3 floor_kd = vec3(1.0f,1.0f,1.0f);
    vec3 floor_ks = vec3(0.0f,0.0f,0.0f);
    vec3 floor_ka = vec3(0.1f,0.1f,0.1f);
    float floor_s = 0.0f;
    
    vec3 wall_center = vec3(0.0f,0.0f,-3.0f);
    vec3 wall_kd = vec3(1.0f,1.0f,1.0f);
    vec3 wall_ks = vec3(0.0f,0.0f,0.0f);
    vec3 wall_ka = vec3(0.1f,0.1f,0.1f);
    float wall_s = 0.0f;
    
    vec3 sph_r1_center = vec3(-0.5f,0.0f,-0.5f);
    vec3 sph_r2_center = vec3(1.5f,0.0f,-1.5f);
    vec3 sph_r1_scale = vec3(1.0f,1.0f,1.0f);
    vec3 sph_r2_scale = vec3(1.0f,1.0f,1.0f);
    
    bool blocklight1 = false;
    bool blocklight2 = false;
    
    bool shadowMode = false;
    bool checkSphere(vec3 center, vec3 dir,vec3 origin, vec3 scale_v3){
        vec3 originaldir = dir;
        rayorigin = origin;
        mat4 scale = glm::scale(scale_v3);
        mat4 trans = glm::translate(glm::mat4(1.0f), center);
        mat4 mv = trans * scale;
        vec3 oc = inverse(mv) * vec4(rayorigin,1);
        dir = inverse(mv) * vec4(dir,0);
        dir = normalize(dir);
        
        float aa = dot(dir,dir);
        float bb = dot(2.0f*dir,oc);
        float cc = dot(oc,oc)-1;
        float dd = pow(bb, 2) - 4*aa*cc;
        
        if (dd < 0) {
            return false;
        }
        else{
            float t1 = (-bb + sqrt(dd)) / (2*aa);
            float t2 = (-bb - sqrt(dd)) / (2*aa);
            x_ray_sphere1 = oc + t1*dir;
            x_ray_sphere2 = oc + t2*dir;
            
            vec3 xp1 = mv * vec4(x_ray_sphere1,1);
            vec3 xp2 = mv * vec4(x_ray_sphere2,1);
            vec3 n1 = transpose(inverse(mv)) * vec4(x_ray_sphere1,0);
            vec3 n2 = transpose(inverse(mv)) * vec4(x_ray_sphere2,0);
            
            if (length(xp1-rayorigin) < length(xp2-rayorigin)) {
                x_ray = xp1;
                normalc = normalize(n1);
            }else{
                x_ray = xp2;
                normalc = normalize(n2);
            }
            if (length(originaldir) < length(x_ray-origin)) {
                return false;
            }
            return true;
        }
    }
    
    bool checkSphere_obj(vec3 center, vec3 dir,vec3 origin, vec3 scale_v3){
        rayorigin = origin;
        mat4 scale = glm::scale(scale_v3);
        mat4 trans = glm::translate(glm::mat4(1.0f), center);
        mat4 mv = trans * scale;
        vec3 oc = inverse(mv) * vec4(rayorigin,1);
        dir = inverse(mv) * vec4(dir,0);
        dir = normalize(dir);
        
        float aa = dot(dir,dir);
        float bb = dot(2.0f*dir,oc);
        float cc = dot(oc,oc)-1;
        float dd = pow(bb, 2) - 4*aa*cc;
        
        if (dd < 0) {
            return false;
        }
        else{
            float t1 = (-bb + sqrt(dd)) / (2*aa);
            float t2 = (-bb - sqrt(dd)) / (2*aa);
            x_ray_sphere1 = oc + t1*dir;
            x_ray_sphere2 = oc + t2*dir;
            
            vec3 xp1 = mv * vec4(x_ray_sphere1,1);
            vec3 xp2 = mv * vec4(x_ray_sphere2,1);
            vec3 n1 = transpose(inverse(mv)) * vec4(x_ray_sphere1,0);
            vec3 n2 = transpose(inverse(mv)) * vec4(x_ray_sphere2,0);
            
            if (length(xp1-rayorigin) < length(xp2-rayorigin)) {
                x_ray = xp1;
                normalc = normalize(n1);
            }else{
                x_ray = xp2;
                normalc = normalize(n2);
            }
            return true;
        }
    }
    
    
    
    bool checkEllip(vec3 dir,vec3 origin){
        rayorigin = origin;
        mat4 scale = glm::scale(ellip_scale);
        mat4 trans = glm::translate(glm::mat4(1.0f), ellip_center);
        mat4 mv = trans * scale;
        vec3 oc = inverse(mv) * vec4(rayorigin,1);
        dir = inverse(mv) * vec4(dir,0);
        dir = normalize(dir);
        
        float aa = dot(dir,dir);
        float bb = dot(2.0f*dir,oc);
        float cc = dot(oc,oc)-1;
        float dd = pow(bb, 2) - 4*aa*cc;
        
        if (dd < 0) {
            return false;
        }
        else{
            float t1 = (-bb + sqrt(dd)) / (2*aa);
            float t2 = (-bb - sqrt(dd)) / (2*aa);
            x_ray_sphere1 = oc + t1*dir;
            x_ray_sphere2 = oc + t2*dir;
            
            vec3 xp1 = mv * vec4(x_ray_sphere1,1);
            vec3 xp2 = mv * vec4(x_ray_sphere2,1);
            vec3 n1 = transpose(inverse(mv)) * vec4(x_ray_sphere1,0);
            vec3 n2 = transpose(inverse(mv)) * vec4(x_ray_sphere2,0);
            
            if (length(xp1-rayorigin) < length(xp2-rayorigin)) {
                x_ray = xp1;
                normalc = normalize(n1);
            }else{
                x_ray = xp2;
                normalc = normalize(n2);
            }
            
            return true;
        }
    }
    
    bool checkPlane(vec3 dir, vec3 origin, vec3 center){
        normalc = vec3(0.0f,1.0f,0.0f);
        float t = dot(normalc,center-origin)/dot(normalc,dir);
        x_ray = origin + t*dir;
        
        if (dot(normalc,dir) >= -0.001) {
            return false;
        }else{
            return true;
        }
    }
    
    bool checkWall(vec3 dir, vec3 origin, vec3 center){
        normalc = vec3(0.0f,0.0f,1.0f);
        float t = dot(normalc,center-origin)/dot(normalc,dir);
        x_ray = origin + t*dir;
        
        if (x_ray.y < -1) {
            return false;
        }else{
            return true;
        }
    }
    
    bool checkWall2(vec3 dir, vec3 origin, vec3 center){
        normalc = vec3(0.0f,0.0f,1.0f);
        float t = dot(normalc,center-origin)/dot(normalc,dir);
        x_ray = origin + t*dir;
    
        if (dot(normalc,dir) >= -0.001f) {
            return false;
        }else{
            
            return true;
        }
    }
    
    int shadow = 0;
    void shading(vec3 normal, vec3 point, string color){
        vec3 ka;
        vec3 kd;
        vec3 ks;
        float s = 0.0f;
        float intensity1 = 1.0f;
        float intensity2 = 0.0f;
        vec3 light = this->light;
        vec3 light2 = this->light2;
        if (color == "blue") {
            ka = ka_blue;
            kd = kd_blue;
            ks = ks_blue;
            s = s_blue;
        }else if (color == "red"){
            ka = ka_red;
            kd = kd_red;
            ks = ks_red;
            s = s_red;
        }else if (color == "green"){
            ka = ka_green;
            kd = kd_green;
            ks = ks_green;
            s = s_green;
        }else if (color == "sphere"){
            ka = sphere_ka;
            kd = sphere_kd;
            ks = sphere_ks;
            s = sphere_s;
            intensity1 = this->intensity1;
            intensity2 = this->intensity2;
            light = this->light1;
        }else if (color == "ellip"){
            ka = ellip_ka;
            kd = ellip_kd;
            ks = ellip_ks;
            s = ellip_s;
            intensity1 = this->intensity1;
            intensity2 = this->intensity2;
            light = this->light1;
        }else if (color == "plane"){
            ka = plane_ka;
            kd = plane_kd;
            ks = plane_ks;
            s = plane_s;
            intensity1 = this->intensity1;
            intensity2 = this->intensity2;
            light = this->light1;
        }else if (color == "sphere_red"){
            ka = sph_red_ka;
            kd = sph_red_kd;
            ks = sph_red_ks;
            s = sph_red_s;
            intensity1 = this->intensity1;
            intensity2 = this->intensity2;
            light = this->light11;
            light2 = this->light22;
        }else if (color == "sphere_blue"){
            ka = sph_blue_ka;
            kd = sph_blue_kd;
            ks = sph_blue_ks;
            s = sph_blue_s;
            intensity1 = this->intensity1;
            intensity2 = this->intensity2;
            light = this->light11;
            light2 = this->light22;
        }else if (color == "plane2"){
            ka = floor_ka;
            kd = floor_kd;
            ks = floor_ks;
            s = floor_s;
            intensity1 = this->intensity1;
            intensity2 = this->intensity2;
            light = this->light11;
            light2 = this->light22;
        }
        vec3 n = normalize(normal);
        
        vec3 halfvert = normalize(normalize(light - point) + normalize(rayorigin-point));
        vec4 diff_color = vec4(kd,1.0) * maxm(0.0,dot(normalize(light - point), n));
        float a = pow(maxm(0.0,dot(halfvert, n)),s);
        vec4 spec_color = vec4(ks,1.0)*a;
        
        vec3 halfvert2 = normalize(normalize(light2 - point) + normalize(rayorigin-point));
        vec4 diff_color2 = vec4(kd,1.0) * maxm(0.0,dot(normalize(light2 - point), n));
        float a2 = pow(maxm(0.0,dot(halfvert2, n)),s);
        vec4 spec_color2 = vec4(ks,1.0)*a2;
        
        if (shadow == 2) {
            diff_color2 = vec4(0);
            spec_color2 = vec4(0);
        }else if (shadow == 1){
            diff_color = vec4(0);
            spec_color = vec4(0);
        }
        
        gl_FragColor = intensity1 * (vec4(ka,1.0) + diff_color + spec_color) + intensity2 * (vec4(ka,1.0) + diff_color2 + spec_color2);
        shadow = 0;
        if (gl_FragColor.z > 1.0f) {
            gl_FragColor.z = 1;
        }
        if (gl_FragColor.x > 1.0f) {
            gl_FragColor.x = 1;
        }
        if (gl_FragColor.y > 1.0f) {
            gl_FragColor.y = 1;
        }
    }
    
    int shadow_shading(vec3 ray, vec3 center, vec3 scale, vec3 normal, string color){
        if (checkSphere(center, light1 - ray, ray, scale) && checkSphere(center, light2 - ray, ray, scale)) {
            blocklight1 = true;
            blocklight2 = true;
            return 1; //0.1
        }else if (checkSphere(center, light1 - ray, ray, scale)){
            if (blocklight1 == false) {
                blocklight1 = true;
            }
            if (blocklight2 == true) {
                return 1;
            }else{
                shadow = 1;
                shading(normal,ray,color);
                shadow = 0;
                return 2;
            }
        }else if (checkSphere(center, light2 - ray, ray, scale)){
            if (blocklight2 == false) {
                blocklight2 = true;
            }
            if (blocklight1 == true) {
                return 1;
            }else{
                shadow = 2;
                shading(normal,ray,color);
                shadow = 0;
                return 3;
            }
            
        }
        return 0;
    }
    int shadow_shading2(vec3 ray, vec3 center, vec3 scale, vec3 normal, string color){
        if (checkSphere(center, light11 - ray, ray, scale) && checkSphere(center, light22 - ray, ray, scale)) {
            blocklight1 = true;
            blocklight2 = true;
            return 1; //0.1
        }else if (checkSphere(center, light11 - ray, ray, scale)){
            if (blocklight1 == false) {
                blocklight1 = true;
            }
            if (blocklight2 == true) {
                return 1;
            }else{
                shadow = 1;
                shading(normal,ray,color);
                shadow = 0;
                return 2;
            }
        }else if (checkSphere(center, light22 - ray, ray, scale)){
            if (blocklight2 == false) {
                blocklight2 = true;
            }
            if (blocklight1 == true) {
                return 1;
            }else{
                shadow = 2;
                shading(normal,ray,color);
                shadow = 0;
                return 3;
            }
            
        }
        return 0;
    }
};

void computeShadow(Color scene3_color, vec3 &colorPixel, vec3 ray, vec3 normal){
    scene3_color.blocklight1 = false;
    scene3_color.blocklight2 = false;
    
    vec3 black = vec3(0.1f,0.1f,0.1f);
    
    int choice = scene3_color.shadow_shading2(ray, scene3_color.sph_r1_center, scene3_color.sph_r1_scale, normal, "plane2");
    if (choice == 1) {
        colorPixel = black;
    }else if(choice == 2 || choice == 3){
        colorPixel = scene3_color.gl_FragColor;
    }
    
    // r2 - light1 - shadow floor
    choice = scene3_color.shadow_shading2(ray, scene3_color.sph_r2_center, scene3_color.sph_r2_scale, normal, "plane2");
    if (choice == 1) {
        colorPixel = black;
    }else if(choice == 2 || choice == 3){
        colorPixel = scene3_color.gl_FragColor;
    }
    // r2 - light2 - shadow floor
    //blue ball
    choice = scene3_color.shadow_shading2(ray, scene3_color.sph_blue_center, scene3_color.sph_blue_scale, normal, "plane2");
    if (choice == 1) {
        colorPixel = black;
    }else if(choice == 2 || choice == 3){
        colorPixel = scene3_color.gl_FragColor;
    }
    //red ball - light 12
    choice = scene3_color.shadow_shading2(ray, scene3_color.sph_red_center, scene3_color.sph_red_scale, normal, "plane2");
    if (choice == 1) {
        colorPixel = black;
    }else if(choice == 2 || choice == 3){
        colorPixel = scene3_color.gl_FragColor;
    }
    
}

int main(int argc, char **argv)
{
    Color scene1_color;
	shared_ptr<Camera> camera;
    camera = make_shared<Camera>();
    
    int scene = atoi(argv[1]);
    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    auto image = make_shared<Image>(width, height);
    vector<vector<vec3>> v;
    
    float fovy = camera->getFovy();
    for (int i = 0; i < height; i++) {
        vector<vec3> innerv;
        for (int j = 0; j < width; j++) {
            float x = -tan(fovy/2) + (1+2*j)*tan(fovy/2)/width;
            float y = -tan(fovy/2) + (1+2*i)*tan(fovy/2)/width;
            vec3 dirc = normalize(vec3(x,y,-1));
            innerv.push_back(dirc);
        }
        v.push_back(innerv);
    }
    
    if (scene == 1) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                vec3 dir = v[i][j];
                if (scene1_color.checkSphere_obj(scene1_color.center_blue, dir, scene1_color.camara, scene1_color.scale_blue)) {
                    scene1_color.shading(scene1_color.normalc,scene1_color.x_ray,"blue");
                    image->setPixel(j, i, scene1_color.gl_FragColor.r*255, scene1_color.gl_FragColor.g*255, scene1_color.gl_FragColor.b*255);
                }
                if (scene1_color.checkSphere_obj(scene1_color.center_green, dir,scene1_color.camara, scene1_color.scale_green)) {
                    scene1_color.shading(scene1_color.normalc,scene1_color.x_ray,"green");
                    image->setPixel(j, i, scene1_color.gl_FragColor.r*255, scene1_color.gl_FragColor.g*255, scene1_color.gl_FragColor.b*255);
                    if (scene1_color.checkSphere_obj(scene1_color.center_red, scene1_color.light-scene1_color.x_ray,scene1_color.x_ray, scene1_color.scale_red)) {
                        image->setPixel(j, i, scene1_color.ka_green.r*255, scene1_color.ka_green.g*255, scene1_color.ka_green.b*255);
                    }
                    if (scene1_color.checkSphere_obj(scene1_color.center_blue, scene1_color.light-scene1_color.x_ray,scene1_color.x_ray, scene1_color.scale_blue)) {
                        image->setPixel(j, i, scene1_color.ka_green.r*255, scene1_color.ka_green.g*255, scene1_color.ka_green.b*255);
                    }
                }
                if (scene1_color.checkSphere_obj(scene1_color.center_red, dir,scene1_color.camara, scene1_color.scale_red)) {
                    scene1_color.shading(scene1_color.normalc,scene1_color.x_ray,"red");
                    image->setPixel(j, i, scene1_color.gl_FragColor.r*255, scene1_color.gl_FragColor.g*255, scene1_color.gl_FragColor.b*255);
                }
            }
        }
    }
    
    
    if (scene == 2) {
        vector<vec2> mark;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                vec3 dir = v[i][j];
                Color scene2_color;
                if (scene2_color.checkPlane(dir, scene2_color.camara,scene2_color.plane_center)) {
                    scene2_color.shading(scene2_color.normalc,scene2_color.x_ray,"plane");
                    image->setPixel(j, i, scene2_color.gl_FragColor.r*255, scene2_color.gl_FragColor.g*255, scene2_color.gl_FragColor.b*255);
                    
                    vec3 ray = scene2_color.x_ray;
                    vec3 normal = scene2_color.normalc;
                    //sphere
                        int choice = scene2_color.shadow_shading(ray, scene2_color.sphere_center, scene2_color.sphere_scale, normal, "plane");
                        if (choice == 1) {
                            image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                        }else if(choice == 2 || choice == 3){
                            image->setPixel(j, i, scene2_color.gl_FragColor.r*255,scene2_color.gl_FragColor.g*255,scene2_color.gl_FragColor.g*255);
                        }
                    //ellip
                        choice = scene2_color.shadow_shading(ray, scene2_color.ellip_center, scene2_color.ellip_scale,normal,"plane");
                        if (choice == 1) {
                            image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                        }else if(choice == 2 || choice == 3){
                            image->setPixel(j, i, scene2_color.gl_FragColor.r*255,scene2_color.gl_FragColor.g*255,scene2_color.gl_FragColor.g*255);
                            
                        }
                }
                if (scene2_color.checkSphere_obj(scene2_color.sphere_center, dir, scene2_color.camara, scene2_color.sphere_scale)) {
                    scene2_color.shading(scene2_color.normalc,scene2_color.x_ray,"sphere");
                    image->setPixel(j, i, scene2_color.gl_FragColor.r*255, scene2_color.gl_FragColor.g*255, scene2_color.gl_FragColor.b*255);
                    
                    if (scene2_color.checkEllip(scene2_color.light1 - scene2_color.x_ray, scene2_color.x_ray)) {
                        image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                    }
                }
                if (scene2_color.checkEllip(dir, scene2_color.camara)) {
                    scene2_color.shading(scene2_color.normalc,scene2_color.x_ray,"ellip");
                    image->setPixel(j, i, scene2_color.gl_FragColor.r*255, scene2_color.gl_FragColor.g*255, scene2_color.gl_FragColor.b*255);
                }
            }
        }
    }
    
    
    if (scene == 3) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                vec3 dir = v[i][j];
                Color scene3_color;
                vec3 colorPixel;
                if (scene3_color.checkPlane(dir, scene3_color.camara,scene3_color.floor_center)) {
                    
                    scene3_color.shading(scene3_color.normalc, scene3_color.x_ray,"plane2");
                    vec3 ray = scene3_color.x_ray;
                    vec3 normal = scene3_color.normalc;
                    colorPixel = scene3_color.gl_FragColor;
                    computeShadow(scene3_color,colorPixel,ray,normal);
                   
                    image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                }
                // wall
                if (scene3_color.checkWall(dir, scene3_color.camara, scene3_color.wall_center)) {
                    
                    scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "plane2");
                    vec3 ray = scene3_color.x_ray;
                    vec3 normal = scene3_color.normalc;
                    colorPixel = scene3_color.gl_FragColor;
                    computeShadow(scene3_color,colorPixel,ray,normal);
                    
                    image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                }
                // r2 bottom
                vec3 color_r1_floor;
                if (scene3_color.checkSphere_obj(scene3_color.sph_r2_center, dir, scene3_color.camara, scene3_color.sph_r2_scale)) {
                    vec3 refl_ray = dir - scene3_color.normalc*(2*dot(scene3_color.normalc,dir));
                    if (scene3_color.checkPlane(refl_ray, scene3_color.x_ray, scene3_color.floor_center)) {
                        
                        scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "plane2");
                        vec3 ray = scene3_color.x_ray;
                        vec3 normal = scene3_color.normalc;
                        colorPixel = scene3_color.gl_FragColor;
                        computeShadow(scene3_color,colorPixel,ray,normal);
                        
                        image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                        color_r1_floor = colorPixel;
                    }
                }
                // r2 top
                if (scene3_color.checkSphere_obj(scene3_color.sph_r2_center, dir, scene3_color.camara, scene3_color.sph_r2_scale)) {
                    vec3 refl_ray = dir - scene3_color.normalc*(2*dot(scene3_color.normalc,dir));
                    if (scene3_color.checkWall(refl_ray, scene3_color.x_ray, scene3_color.wall_center)) {
                        
                        scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "plane2");
                        vec3 ray = scene3_color.x_ray;
                        vec3 normal = scene3_color.normalc;
                        colorPixel = scene3_color.gl_FragColor;
                        computeShadow(scene3_color,colorPixel,ray,normal);
                        
                        image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                    }
                    if (scene3_color.checkWall2(refl_ray, scene3_color.x_ray, scene3_color.wall_center) == false) {
                        if (dir.y > 0) {
                            image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                        }else{
                            image->setPixel(j, i, color_r1_floor.r*255, color_r1_floor.g*255, color_r1_floor.b*255);
                        }
                    }
                }
                
                // r2 bottom
                vec3 color_r2_floor;
                if (scene3_color.checkSphere_obj(scene3_color.sph_r1_center, dir, scene3_color.camara, scene3_color.sph_r1_scale)) {
                    vec3 refl_ray = dir - scene3_color.normalc*(2*dot(scene3_color.normalc,dir));
                    if (scene3_color.checkPlane(refl_ray, scene3_color.x_ray, scene3_color.floor_center)) {
                        
                        scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "plane2");
                        vec3 ray = scene3_color.x_ray;
                        vec3 normal = scene3_color.normalc;
                        colorPixel = scene3_color.gl_FragColor;
                        computeShadow(scene3_color,colorPixel,ray,normal);
                        
                        image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                        color_r2_floor = colorPixel;
                    }
                }
                // r2 top
                if (scene3_color.checkSphere_obj(scene3_color.sph_r1_center, dir, scene3_color.camara, scene3_color.sph_r1_scale)) {
                    vec3 refl_ray = dir - scene3_color.normalc*(2*dot(scene3_color.normalc,dir));
                    if (scene3_color.checkWall(refl_ray, scene3_color.x_ray, scene3_color.wall_center)) {
                        
                        scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "plane2");
                        vec3 ray = scene3_color.x_ray;
                        vec3 normal = scene3_color.normalc;
                        colorPixel = scene3_color.gl_FragColor;
                        computeShadow(scene3_color,colorPixel,ray,normal);
                    }
                    if (scene3_color.checkWall2(refl_ray, scene3_color.x_ray, scene3_color.wall_center) == false) {
                        if (dir.y > 0) {
                            colorPixel = vec3(0.1f,0.1f,0.1f);
                        }else{
                            colorPixel = color_r2_floor;
                        }
                    }
                    image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                }
                
                //// blue sphere
                if (scene3_color.checkSphere_obj(scene3_color.sph_blue_center, dir, scene3_color.camara,scene3_color.sph_blue_scale)) {
                    scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_blue");
                    image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                }
                
                //// r1 red blue reflection
                if (scene3_color.checkSphere_obj(scene3_color.sph_r1_center, dir, scene3_color.camara, scene3_color.sph_r1_scale)) {
                    if (dir.y < -0.001f) {
                        vec3 refl_ray = dir - scene3_color.normalc*(2*dot(scene3_color.normalc,dir));
                        if (scene3_color.checkSphere_obj(scene3_color.sph_blue_center, refl_ray, scene3_color.x_ray, scene3_color.sph_blue_scale)) {
                            scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_blue");
                            image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                        }
                    }
                }
                
                if (scene3_color.checkSphere_obj(scene3_color.sph_r1_center, dir, scene3_color.camara, scene3_color.sph_r1_scale)) {
                    if (dir.y < -0.001f) {
                        vec3 refl_ray = -dir + scene3_color.normalc* (dot(scene3_color.normalc,dir)*2);
                        if (scene3_color.checkSphere_obj(scene3_color.sph_red_center, refl_ray, scene3_color.x_ray, scene3_color.sph_red_scale)) {
                            scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_red");
                            image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                        }
                    }
                }
                //// red sphere
                if (scene3_color.checkSphere_obj(scene3_color.sph_red_center, dir, scene3_color.camara,scene3_color.sph_red_scale)) {
                    scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_red");
                    image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                }
                
                ///// r2 red blue reflection
                if (scene3_color.checkSphere_obj(scene3_color.sph_r2_center, dir, scene3_color.camara, scene3_color.sph_r2_scale)) {
                    if (dir.y < -0.001f) {
                        vec3 refl_ray = dir - scene3_color.normalc*(2*dot(scene3_color.normalc,dir));
                        if (scene3_color.checkSphere_obj(scene3_color.sph_red_center, refl_ray, scene3_color.x_ray, scene3_color.sph_red_scale)) {
                            scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_red");
                            image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                        }
                    }
                }
                if (scene3_color.checkSphere_obj(scene3_color.sph_r2_center, dir, scene3_color.camara, scene3_color.sph_r2_scale)) {
                    if (dir.y < -0.001f) {
                        vec3 refl_ray = dir - scene3_color.normalc*(2*dot(scene3_color.normalc,dir));
                        if (scene3_color.checkSphere_obj(scene3_color.sph_blue_center, refl_ray, scene3_color.x_ray, scene3_color.sph_blue_scale)) {
                            scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_blue");
                            image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                        }
                    }
                }
                
                // r2 on r1
                if (scene3_color.checkSphere_obj(scene3_color.sph_r1_center, dir, scene3_color.camara, scene3_color.sph_r1_scale)) {
                    vec3 refl_ray = dir - scene3_color.normalc*(2*dot(scene3_color.normalc,dir));
                    if (scene3_color.checkSphere_obj(scene3_color.sph_r2_center, refl_ray, scene3_color.x_ray, scene3_color.sph_r2_scale) && dir.x > 0) {
                        vec3 xray= scene3_color.x_ray;
                        refl_ray = refl_ray - scene3_color.normalc*(2*dot(scene3_color.normalc,refl_ray));
                        
                        vec3 color_r1_floor;
                        if (scene3_color.checkPlane(refl_ray, xray,scene3_color.floor_center)) {
                            
                            scene3_color.shading(scene3_color.normalc, scene3_color.x_ray,"plane2");
                            vec3 ray = scene3_color.x_ray;
                            vec3 normal = scene3_color.normalc;
                            colorPixel = scene3_color.gl_FragColor;
                            computeShadow(scene3_color,colorPixel,ray,normal);
                            
                            image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                            color_r1_floor = colorPixel;
                        }
                        
                        if (scene3_color.checkWall(refl_ray, xray, scene3_color.wall_center)) {
                            
                            scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "plane2");
                            vec3 ray = scene3_color.x_ray;
                            vec3 normal = scene3_color.normalc;
                            colorPixel = scene3_color.gl_FragColor;
                            computeShadow(scene3_color,colorPixel,ray,normal);
                            
                            image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                            if (scene3_color.checkWall2(refl_ray, scene3_color.x_ray, scene3_color.wall_center) == false) {
                                if (dir.y > 0) {
                                    image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                                }else{
                                    image->setPixel(j, i, color_r1_floor.r*255, color_r1_floor.g*255, color_r1_floor.b*255);
                                }
                            }
                             
                        }else{
                            if (dir.y > -0.001f) {
                                image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                            }
                        }
                        if (dir.y < -0.001f) {
                            
                            if (scene3_color.checkSphere_obj(scene3_color.sph_red_center, refl_ray, xray,scene3_color.sph_red_scale)) {
                                scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_red");
                                image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                            }
                            if (scene3_color.checkSphere_obj(scene3_color.sph_blue_center, refl_ray, xray, scene3_color.sph_blue_scale)) {
                                scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_blue");
                                image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                                
                            }
                        }
                        if (scene3_color.checkSphere(scene3_color.sph_r1_center, refl_ray, xray, scene3_color.sph_r1_scale)) {
                            //image->setPixel(j, i, 0, 0, 0);
                            vec3 refl_ray2 = refl_ray - scene3_color.normalc*(2*dot(scene3_color.normalc,refl_ray));
                            vec3 xray2= scene3_color.x_ray;
                            
                            vec3 color_r1_floor;
                            if (scene3_color.checkPlane(refl_ray2, xray2,scene3_color.floor_center)) {
                                
                                scene3_color.shading(scene3_color.normalc, scene3_color.x_ray,"plane2");
                                vec3 ray = scene3_color.x_ray;
                                vec3 normal = scene3_color.normalc;
                                colorPixel = scene3_color.gl_FragColor;
                                computeShadow(scene3_color,colorPixel,ray,normal);
                                
                                image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                                color_r1_floor = colorPixel;
                            }
                            
                            if (scene3_color.checkWall(refl_ray2, xray2, scene3_color.wall_center)) {
                                
                                scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "plane2");
                                vec3 ray = scene3_color.x_ray;
                                vec3 normal = scene3_color.normalc;
                                colorPixel = scene3_color.gl_FragColor;
                                computeShadow(scene3_color,colorPixel,ray,normal);
                                
                                image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                                if (scene3_color.checkWall2(refl_ray2, scene3_color.x_ray, scene3_color.wall_center) == false) {
                                    if (dir.y > 0) {
                                        image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                                    }else{
                                        image->setPixel(j, i, color_r1_floor.r*255, color_r1_floor.g*255, color_r1_floor.b*255);
                                    }
                                }
                            }else{
                                if (dir.y >= 0) {
                                    image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                                }
                            }
                            
                            if (dir.y < -0.001f) {
                                if (scene3_color.checkSphere_obj(scene3_color.sph_red_center, refl_ray2, xray2,scene3_color.sph_red_scale)) {
                                    scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_red");
                                    image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                                }
                                if (scene3_color.checkSphere_obj(scene3_color.sph_blue_center, refl_ray2, xray2, scene3_color.sph_blue_scale)) {
                                    scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_blue");
                                    image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                                    
                                }
                            }
                            if (scene3_color.checkSphere(scene3_color.sph_r2_center, refl_ray2, xray2, scene3_color.sph_r2_scale)) {
                                //image->setPixel(j, i, 0, 0, 0);
                                vec3 refl_ray3 = refl_ray2 - scene3_color.normalc*(2*dot(scene3_color.normalc,refl_ray2));
                                vec3 xray3= scene3_color.x_ray;
                                
                                vec3 color_r1_floor;
                                if (scene3_color.checkPlane(refl_ray2, xray2,scene3_color.floor_center)) {
                                    
                                    scene3_color.shading(scene3_color.normalc, scene3_color.x_ray,"plane2");
                                    vec3 ray = scene3_color.x_ray;
                                    vec3 normal = scene3_color.normalc;
                                    colorPixel = scene3_color.gl_FragColor;
                                    computeShadow(scene3_color,colorPixel,ray,normal);
                                    
                                    image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                                    color_r1_floor = colorPixel;
                                }
                                
                                if (scene3_color.checkWall(refl_ray2, xray2, scene3_color.wall_center)) {
                                    
                                    scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "plane2");
                                    vec3 ray = scene3_color.x_ray;
                                    vec3 normal = scene3_color.normalc;
                                    colorPixel = scene3_color.gl_FragColor;
                                    computeShadow(scene3_color,colorPixel,ray,normal);
                                    
                                    image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                                    if (scene3_color.checkWall2(refl_ray2, scene3_color.x_ray, scene3_color.wall_center) == false) {
                                        if (dir.y > 0) {
                                            image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                                        }else{
                                            image->setPixel(j, i, color_r1_floor.r*255, color_r1_floor.g*255, color_r1_floor.b*255);
                                        }
                                    }
                                }else{
                                    if (dir.y >= 0) {
                                        image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                                    }
                                }
                                
                                if (dir.y < -0.001f) {
                                    if (scene3_color.checkSphere_obj(scene3_color.sph_red_center, refl_ray3, xray3,scene3_color.sph_red_scale)) {
                                        scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_red");
                                        image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                                    }
                                    if (scene3_color.checkSphere_obj(scene3_color.sph_blue_center, refl_ray3, xray3, scene3_color.sph_blue_scale)) {
                                        scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_blue");
                                        image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                                        
                                    }
                                }
                            }
                        }
                    }
                    
                }
                
                // r1 on r2
                if (scene3_color.checkSphere_obj(scene3_color.sph_r2_center, dir, scene3_color.camara, scene3_color.sph_r2_scale)) {
                    vec3 refl_ray = dir - scene3_color.normalc*(2*dot(scene3_color.normalc,dir));
                    if (scene3_color.checkSphere(scene3_color.sph_r1_center, refl_ray, scene3_color.x_ray, scene3_color.sph_r1_scale)) {
                        vec3 xray= scene3_color.x_ray;
                        refl_ray = refl_ray - scene3_color.normalc*(2*dot(scene3_color.normalc,refl_ray));
                        
                        vec3 color_r1_floor;
                        if (scene3_color.checkPlane(refl_ray, xray,scene3_color.floor_center)) {
                            
                            scene3_color.shading(scene3_color.normalc, scene3_color.x_ray,"plane2");
                            vec3 ray = scene3_color.x_ray;
                            vec3 normal = scene3_color.normalc;
                            colorPixel = scene3_color.gl_FragColor;
                            computeShadow(scene3_color,colorPixel,ray,normal);
                            
                            image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                            color_r1_floor = colorPixel;
                        }
                        
                        if (scene3_color.checkWall(refl_ray, xray, scene3_color.wall_center)) {
                            
                            scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "plane2");
                            vec3 ray = scene3_color.x_ray;
                            vec3 normal = scene3_color.normalc;
                            colorPixel = scene3_color.gl_FragColor;
                            computeShadow(scene3_color,colorPixel,ray,normal);
                            
                            image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                            if (scene3_color.checkWall2(refl_ray, scene3_color.x_ray, scene3_color.wall_center) == false) {
                                if (dir.y > -0.001f) {
                                    image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                                }else{
                                    image->setPixel(j, i, color_r1_floor.r*255, color_r1_floor.g*255, color_r1_floor.b*255);
                                }
                            }
                        }
                        if (dir.y < -0.001f) {
                            
                            if (scene3_color.checkSphere_obj(scene3_color.sph_red_center, refl_ray, xray,scene3_color.sph_red_scale)) {
                                scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_red");
                                image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                            }
                            if (scene3_color.checkSphere_obj(scene3_color.sph_blue_center, refl_ray, xray, scene3_color.sph_blue_scale)) {
                                scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_blue");
                                image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                                
                            }
                        }
                        if (scene3_color.checkSphere(scene3_color.sph_r2_center, refl_ray, xray, scene3_color.sph_r2_scale)) {
                            //image->setPixel(j, i, 0, 0, 0);
                            vec3 refl_ray2 = refl_ray - scene3_color.normalc*(2*dot(scene3_color.normalc,refl_ray));
                            vec3 xray2= scene3_color.x_ray;
                            
                            vec3 color_r1_floor;
                            if (scene3_color.checkPlane(refl_ray2, xray2,scene3_color.floor_center)) {
                                
                                scene3_color.shading(scene3_color.normalc, scene3_color.x_ray,"plane2");
                                vec3 ray = scene3_color.x_ray;
                                vec3 normal = scene3_color.normalc;
                                colorPixel = scene3_color.gl_FragColor;
                                computeShadow(scene3_color,colorPixel,ray,normal);
                                
                                image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                                color_r1_floor = colorPixel;
                            }
                            
                            if (scene3_color.checkWall(refl_ray2, xray2, scene3_color.wall_center)) {
                                
                                scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "plane2");
                                vec3 ray = scene3_color.x_ray;
                                vec3 normal = scene3_color.normalc;
                                colorPixel = scene3_color.gl_FragColor;
                                computeShadow(scene3_color,colorPixel,ray,normal);
                                
                                image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                                if (scene3_color.checkWall2(refl_ray2, scene3_color.x_ray, scene3_color.wall_center) == false) {
                                    if (dir.y > -0.0001f) {
                                        image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                                    }else{
                                        image->setPixel(j, i, color_r1_floor.r*255, color_r1_floor.g*255, color_r1_floor.b*255);
                                    }
                                }
                            }else{
                                if (dir.y > -0.0001f) {
                                    image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                                }
                            }
                            
                            
                            if (dir.y < -0.0001f) {
                                if (scene3_color.checkSphere_obj(scene3_color.sph_red_center, refl_ray2, xray2,scene3_color.sph_red_scale)) {
                                    scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_red");
                                    image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                                }
                                if (scene3_color.checkSphere_obj(scene3_color.sph_blue_center, refl_ray2, xray2, scene3_color.sph_blue_scale)) {
                                    scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_blue");
                                    image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                                    
                                }
                            }
                            if (scene3_color.checkSphere(scene3_color.sph_r1_center, refl_ray2, xray2, scene3_color.sph_r1_scale)) {
                                //image->setPixel(j, i, 0, 0, 0);
                                vec3 refl_ray3 = refl_ray2 - scene3_color.normalc*(2*dot(scene3_color.normalc,refl_ray2));
                                vec3 xray3= scene3_color.x_ray;
                                
                                vec3 color_r2_floor;
                                if (scene3_color.checkPlane(refl_ray3, xray3,scene3_color.floor_center)) {
                                    
                                    scene3_color.shading(scene3_color.normalc, scene3_color.x_ray,"plane2");
                                    vec3 ray = scene3_color.x_ray;
                                    vec3 normal = scene3_color.normalc;
                                    colorPixel = scene3_color.gl_FragColor;
                                    computeShadow(scene3_color,colorPixel,ray,normal);
                                    
                                    image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                                    color_r2_floor = colorPixel;
                                }
                                
                                if (scene3_color.checkWall(refl_ray3, xray3, scene3_color.wall_center)) {
                                    
                                    scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "plane2");
                                    vec3 ray = scene3_color.x_ray;
                                    vec3 normal = scene3_color.normalc;
                                    colorPixel = scene3_color.gl_FragColor;
                                    computeShadow(scene3_color,colorPixel,ray,normal);
                                    
                                    image->setPixel(j, i, colorPixel.r*255, colorPixel.g*255, colorPixel.b*255);
                                    if (scene3_color.checkWall2(refl_ray3, scene3_color.x_ray, scene3_color.wall_center) == false) {
                                        if (dir.y > -0.0001f) {
                                            image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                                        }else{
                                            //image->setPixel(j, i, color_r1_floor.r*255, color_r2_floor.g*255, color_r2_floor.b*255);
                                        }
                                    }
                                }else{
                                    if (dir.y > -0.0001f) {
                                        image->setPixel(j, i, 0.1*255, 0.1*255, 0.1*255);
                                    }
                                }
                                
                                if (dir.y < -0.0001f) {
                                    if (scene3_color.checkSphere_obj(scene3_color.sph_red_center, refl_ray3, xray3,scene3_color.sph_red_scale)) {
                                        scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_red");
                                        image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                                    }
                                    if (scene3_color.checkSphere_obj(scene3_color.sph_blue_center, refl_ray3, xray3, scene3_color.sph_blue_scale)) {
                                        scene3_color.shading(scene3_color.normalc, scene3_color.x_ray, "sphere_blue");
                                        image->setPixel(j, i, scene3_color.gl_FragColor.r*255, scene3_color.gl_FragColor.g*255, scene3_color.gl_FragColor.b*255);
                                        
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // scene 4
    if (scene == 4) {
        string meshName(argv[5]);
        vector<float> posBuf; // list of vertex positions
        vector<float> norBuf;
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        string errStr;
        bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
        if(!rc) {
            cerr << errStr << endl;
        } else {
            // Some OBJ files have different indices for vertex positions, normals,
            // and texture coordinates. For example, a cube corner vertex may have
            // three different normals. Here, we are going to duplicate all such
            // vertices.
            // Loop over shapes
            for(size_t s = 0; s < shapes.size(); s++) {
                // Loop over faces (polygons)
                size_t index_offset = 0;
                for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                    size_t fv = shapes[s].mesh.num_face_vertices[f];
                    // Loop over vertices in the face.
                    for(size_t v = 0; v < fv; v++) {
                        // access to vertex
                        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                        posBuf.push_back(attrib.vertices[3*idx.vertex_index+0]);
                        posBuf.push_back(attrib.vertices[3*idx.vertex_index+1]);
                        posBuf.push_back(attrib.vertices[3*idx.vertex_index+2]);
                        if(!attrib.normals.empty()) {
                            norBuf.push_back(attrib.normals[3*idx.normal_index+0]);
                            norBuf.push_back(attrib.normals[3*idx.normal_index+1]);
                            norBuf.push_back(attrib.normals[3*idx.normal_index+2]);
                        }
                    }
                    index_offset += fv;
                    // per-face material (IGNORE)
                    shapes[s].mesh.material_ids[f];
                }
            }
        }
        cout << "Number of vertices: " << posBuf.size()/3 << endl;
        cout << "Number of normals: " << norBuf.size()/3 << endl;
        cout << "Processing ... " << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                Color tri;
                tri.rayorigin = vec3(0.0f,0.0f,5.0f);
                mat4 scale = glm::scale(vec3(1.1f,1.1f,1.1f));
                mat4 trans = glm::translate(glm::mat4(1.0f), vec3(0,-0.5,0));
                mat4 rotate = glm::mat4(1.0f);
                rotate = glm::rotate(trans, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                mat4 mv = trans * rotate *scale;
                vec3 oc = inverse(mv) * vec4(tri.rayorigin,1);
                vec3 dirv = inverse(mv) * vec4(v[i][j],0);
                dirv = normalize(dirv);
                double neworigin[3] = {oc.x,oc.y,oc.z};
                double newdir[3] = {dirv.x,dirv.y,dirv.z};
                
                // acceleration using sphere checking, 1.5 scale sphere here
                if (tri.checkSphere_obj(vec3(0,0,0), v[i][j], tri.rayorigin,  vec3(1.5f,1.5f,1.5f))) {
                    for (int k = 0; k < posBuf.size(); k+=9) {
                        //double orig[3] = {0.0f,0.0f,5.0f};
                        //double dir[3] = {v[i][j].x, v[i][j].y, v[i][j].z};
                        double vert0[3] = {posBuf[k], posBuf[k+1], posBuf[k+2]};
                        double vert1[3] = {posBuf[k+3], posBuf[k+4], posBuf[k+5]};
                        double vert2[3] = {posBuf[k+6], posBuf[k+7], posBuf[k+8]};
                        
                        vec3 normal0 = vec3(norBuf[k], norBuf[k+1], norBuf[k+2]);
                        vec3 normal1 = vec3(norBuf[k+3], norBuf[k+4], norBuf[k+5]);
                        vec3 normal2 = vec3(norBuf[k+6], norBuf[k+7], norBuf[k+8]);
                        
                        double t = 0;
                        double u = 0;
                        double vv = 0;
                        
                        if (intersect_triangle3(neworigin, newdir, vert0, vert1, vert2, &t, &u, &vv) == 1) {
                            if (t > 0) {
                                vec3 xray = tri.rayorigin + float(t)*v[i][j];
                                double w = 1-u-vv;
                                vec3 nor = vec3(w*normal0.x,w*normal0.y,w*normal0.z) + vec3(u*normal1.x,u*normal1.y,u*normal1.z) + vec3(vv*normal2.x,vv*normal2.y,vv*normal2.z);
                                
                                vec3 xp1 = mv * vec4(xray,1);
                                vec3 n1 = normalize(transpose(inverse(mv)) * vec4(nor,0));
                                if (n1.z < 0.0f) {
                                    continue;
                                }else{
                                    tri.shading(n1, xp1, "blue");
                                    image->setPixel(j, i, tri.gl_FragColor.r*255, tri.gl_FragColor.g*255, tri.gl_FragColor.b*255);
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    image->writeToFile(argv[4]);
	return 0;
}
