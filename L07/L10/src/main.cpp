#include <cassert>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "GLSL.h"
#include "MatrixStack.h"
#include "Program.h"
#include "Shape.h"

using namespace std;
using namespace glm;

GLFWwindow *window; // Main application window
string RESOURCE_DIR = "./"; // Where the resources are loaded from

shared_ptr<Camera> camera;
shared_ptr<Program> progShape;
shared_ptr<Program> progSimple;
shared_ptr<Shape> shapeSphere;
shared_ptr<Shape> shapePlane;

class Hit
{
public:
	Hit() : x(0), n(0), t(0) {}
	Hit(const vec3 &x, const vec3 &n, float t) { this->x = x; this->n = n; this->t = t; }
	vec3 x; // position
	vec3 n; // normal
	float t; // distance
};

vec3 ray[2];
vector<Hit> hits;

bool keyToggles[256] = {false}; // only for English keyboards!

// This function is called when a GLFW error occurs
static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

// This function is called when a key is pressed
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

// This function is called when the mouse is clicked
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	// Get the current mouse position.
	double xmouse, ymouse;
	glfwGetCursorPos(window, &xmouse, &ymouse);
	// Get current window size.
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	if(action == GLFW_PRESS) {
		bool shift = (mods & GLFW_MOD_SHIFT) != 0;
		bool ctrl  = (mods & GLFW_MOD_CONTROL) != 0;
		bool alt   = (mods & GLFW_MOD_ALT) != 0;
		camera->mouseClicked((float)xmouse, (float)ymouse, shift, ctrl, alt);
		
		if(shift) {
			hits.clear();
			auto M = make_shared<MatrixStack>();
			M->loadIdentity();
			camera->applyProjectionMatrix(M);
			mat4 P = M->topMatrix();
			M->loadIdentity();
			camera->applyViewMatrix(M);
			mat4 V = M->topMatrix();
			mat4 C = inverse(V);
			
			// Task 1: Update ray
            
            //1. Pixel-> normalized device coords
            ray[0] = C[3];
            float x = ((2.0f * xmouse) / width) - 1.0f;
            float y = 1.0f - (2.0f * ymouse) / height;
            float z = 1.0f;
            vec3 ray_nds = vec3(x, y, z);
            
            //2. normalized device coords -> clip coords
            vec4 ray_clip = vec4(ray_nds.x,ray_nds.y,-1.0, 1.0);
            
            //3. clips -> eye
            vec4 ray_eye = inverse(P) * ray_clip;
            ray_eye = vec4(ray_eye.x,ray_eye.y, -1.0, 1.0);
            
            //4. eye -> world
            vec3 ray_wor = C * ray_eye;
            vec3 v_wor = normalize(ray_wor - ray[0]);
            ray[1] = v_wor;
            
			// Task 2: Find plane intersection
            vec3 c = vec3(0.0f,0.0f,-1.0f);
            vec3 n = vec3(0.0f,0.0f,1.0f);
            float t = dot(n,c-ray[0])/dot(n,ray[1]);
            vec3 x_ray = ray[0] + t*ray[1];
            Hit h = Hit(x_ray, n, t);
            hits.push_back(h);
            
			// Task 3: Find sphere intersection(s)
            float aa = dot(ray[1],ray[1]);
            float bb = dot(2.0f*ray[1],ray[0]);
            float cc = dot(ray[0],ray[0])-1;
            float dd = pow(bb, 2) - 4*aa*cc;
            if (dd > 0) {
                float t1 = (-bb + sqrt(dd)) / (2*aa);
                float t2 = (-bb - sqrt(dd)) / (2*aa);
                vec3 x_ray_sphere1 = ray[0] + t1*ray[1];
                vec3 x_ray_sphere2 = ray[0] + t2*ray[1];
                Hit h1 = Hit(x_ray_sphere1, x_ray_sphere1, t1);
                Hit h2 = Hit(x_ray_sphere2, x_ray_sphere2, t2);
                hits.push_back(h1);
                hits.push_back(h2);
            }
			// Task 4: Find ellipsoid intersection(s)
            
            mat4 mm;
            M->loadIdentity();
            M->translate(1.0f, 1.0f, 0.0f);
            vec3 axis = normalize(vec3(1.0f, 1.0f, 1.0f));
            //camera->applyViewMatrix(M);
            M->rotate(1.0f, axis);
            M->scale(1.5f, 1.0f, 0.5f);
            mm = M->topMatrix();
            vec3 pp = inverse(mm) * vec4(ray[0],1);
            vec3 vp = inverse(mm) * vec4(ray[1],0);
            vp = normalize(vp);
            //cout << "pp" << vp.x << vp.y << vp.z << endl;
            //cout << "ray" << ray[1].x << ray[1].y << ray[1].z<< endl;
            float aa_e = dot(vp,vp);
            float bb_e = dot(2.0f*vp,pp);
            float cc_e = dot(pp,pp)-1;
            float dd_e = pow(bb_e, 2) - 4*aa_e*cc_e;
            //if (dd_e > 0) {
                float t11 = (-bb_e + sqrt(dd_e)) / (2*aa_e);
                float t22 = (-bb_e - sqrt(dd_e)) / (2*aa_e);
                vec3 x_ray_e1 = pp + t11*vp;
                vec3 x_ray_e2 = pp + t22*vp;
                
                vec3 xp1 = mm * vec4(x_ray_e1,1);
                vec3 xp2 = mm * vec4(x_ray_e2,1);
                vec3 n1 = transpose(inverse(mm)) * vec4(x_ray_e1,0);
                vec3 n2 = transpose(inverse(mm)) * vec4(x_ray_e2,0);
            
                Hit h11 = Hit(xp1, normalize(n1), length(vec3(xp1)-ray[0]));
                Hit h22 = Hit(xp2, normalize(n2), length(vec3(xp2)-ray[0]));
                hits.push_back(h11);
                hits.push_back(h22);
            //}
		}
	}
}

// This function is called when the mouse moves
static void cursor_position_callback(GLFWwindow* window, double xmouse, double ymouse)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if(state == GLFW_PRESS) {
		camera->mouseMoved((float)xmouse, (float)ymouse);
	}
}

static void char_callback(GLFWwindow *window, unsigned int key)
{
	keyToggles[key] = !keyToggles[key];
	switch(key) {
	}
}

// If the window is resized, capture the new size and reset the viewport
static void resize_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// This function is called once to initialize the scene and OpenGL
static void init()
{
	// Initialize time.
	glfwSetTime(0.0);
	
	// Set background color.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);

	progShape = make_shared<Program>();
	progShape->setShaderNames(RESOURCE_DIR + "shape_vert.glsl", RESOURCE_DIR + "shape_frag.glsl");
	progShape->setVerbose(true);
	progShape->init();
	progShape->addAttribute("aPos");
	progShape->addAttribute("aNor");
	progShape->addUniform("P");
	progShape->addUniform("MV");
	progShape->addUniform("MVit");
	progShape->setVerbose(false);

	progSimple = make_shared<Program>();
	progSimple->setShaderNames(RESOURCE_DIR + "simple_vert.glsl", RESOURCE_DIR + "simple_frag.glsl");
	progSimple->setVerbose(true);
	progSimple->init();
	progSimple->addAttribute("aPos");
	progSimple->addAttribute("aNor");
	progSimple->addUniform("P");
	progSimple->addUniform("MV");
	progSimple->setVerbose(false);
	
	camera = make_shared<Camera>();
	camera->setInitDistance(5.0f);
	
	// Ray: position and direction
	ray[0] = vec3(0.0f, 0.0f, 5.0f);
	ray[1] = vec3(0.0f, 0.0f, -1.0f);
	
	shapeSphere = make_shared<Shape>();
	shapeSphere->loadMesh(RESOURCE_DIR + "sphere.obj");
	shapeSphere->init();
	
	shapePlane = make_shared<Shape>();
	shapePlane->loadMesh(RESOURCE_DIR + "square.obj");
	shapePlane->init();
	
	GLSL::checkError(GET_FILE_LINE);
}

// This function is called every frame to draw the scene.
static void render()
{
	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(keyToggles[(unsigned)'c']) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}
	if(keyToggles[(unsigned)'z']) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	camera->setAspect((float)width/(float)height);
	
	// Matrix stacks
	auto P = make_shared<MatrixStack>();
	auto MV = make_shared<MatrixStack>();
	
	// Apply camera transforms
	P->pushMatrix();
	camera->applyProjectionMatrix(P);
	MV->pushMatrix();
	camera->applyViewMatrix(MV);
	
	progShape->bind();
	glUniformMatrix4fv(progShape->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	
	// Draw sphere
	glUniformMatrix4fv(progShape->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
	glUniformMatrix4fv(progShape->getUniform("MVit"), 1, GL_FALSE, value_ptr(inverse(transpose(MV->topMatrix()))));
	shapeSphere->draw(progShape);
	
	// Draw ellipsoid
	MV->pushMatrix();
	MV->translate(1.0f, 1.0f, 0.0f);
	vec3 axis = normalize(vec3(1.0f, 1.0f, 1.0f));
	MV->rotate(1.0f, axis);
	MV->scale(1.5f, 1.0f, 0.5f);
    ///////
    //mm = MV->topMatrix();
	glUniformMatrix4fv(progShape->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
	glUniformMatrix4fv(progShape->getUniform("MVit"), 1, GL_FALSE, value_ptr(inverse(transpose(MV->topMatrix()))));
	shapeSphere->draw(progShape);
	MV->popMatrix();
	
	// Draw plane
	MV->pushMatrix();
	MV->translate(0.0f, 0.0f, -1.0f);
	MV->scale(5.0f);
	glUniformMatrix4fv(progShape->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
	glUniformMatrix4fv(progShape->getUniform("MVit"), 1, GL_FALSE, value_ptr(inverse(transpose(MV->topMatrix()))));
	shapePlane->draw(progShape);
	MV->popMatrix();
	progShape->unbind();
	
	// Draw ray
	progSimple->bind();
	glUniformMatrix4fv(progSimple->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	glUniformMatrix4fv(progSimple->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3fv(&ray[0][0]);
	vec3 ray1 = ray[0] + 100.0f * ray[1];
	glVertex3fv(&ray1[0]);
	glEnd();
	
	// Draw hits
	glPointSize(10.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	for(auto hit : hits) {
		glBegin(GL_POINTS);
		glVertex3fv(&hit.x[0]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3fv(&hit.x[0]);
		vec3 x1 = hit.x + 0.5f*hit.n;
		glVertex3fv(&x1[0]);
		glEnd();
	}
	progSimple->unbind();
	
	MV->popMatrix();
	P->popMatrix();
	
	GLSL::checkError(GET_FILE_LINE);
}

int main(int argc, char **argv)
{
	if(argc < 2) {
		cout << "Please specify the resource directory." << endl;
		return 0;
	}
	RESOURCE_DIR = argv[1] + string("/");

	// Set error callback.
	glfwSetErrorCallback(error_callback);
	// Initialize the library.
	if(!glfwInit()) {
		return -1;
	}
	// Create a windowed mode window and its OpenGL context.
	window = glfwCreateWindow(640, 480, "YOUR NAME", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}
	// Make the window's context current.
	glfwMakeContextCurrent(window);
	// Initialize GLEW.
	glewExperimental = true;
	if(glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		return -1;
	}
	glGetError(); // A bug in glewInit() causes an error that we can safely ignore.
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
	GLSL::checkVersion();
	// Set vsync.
	glfwSwapInterval(1);
	// Set keyboard callback.
	glfwSetKeyCallback(window, key_callback);
	// Set char callback.
	glfwSetCharCallback(window, char_callback);
	// Set cursor position callback.
	glfwSetCursorPosCallback(window, cursor_position_callback);
	// Set mouse button callback.
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// Set the window resize call back.
	glfwSetFramebufferSizeCallback(window, resize_callback);
	// Initialize scene.
	init();
	// Loop until the user closes the window.
	while(!glfwWindowShouldClose(window)) {
		// Render scene.
		render();
		// Swap front and back buffers.
		glfwSwapBuffers(window);
		// Poll for and process events.
		glfwPollEvents();
	}
	// Quit program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
