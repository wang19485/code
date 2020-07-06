#include <cassert>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

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

GLFWwindow *window; // Main application window
string RESOURCE_DIR = "./"; // Where the resources are loaded from
string input_obj = "";

shared_ptr<Camera> camera;
shared_ptr<Program> prog;
shared_ptr<Shape> shape;
int mode = 0;
int lightsource = 1;

class Light{
public:
    glm::vec3 light1 = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 light2 = glm::vec3(-1.0f, 1.0f, 1.0f);
    void modify_x(float x, int lights){
        if (lights == 1) {
            light1 = glm::vec3(light1.x + x, light1.y, 1.0f);
        }else{
            light2 = glm::vec3(light2.x + x, light2.y, 1.0f);
        }
    }
    
    void modify_y(float y, int lights){
        if (lights == 1) {
            light1 = glm::vec3(light1.x, light1.y + y, 1.0f);
        }else{
            light2 = glm::vec3(light2.x, light2.y + y, 1.0f);
        }
    }
};

Light L;

class Material{
public:
    void mode0(){ // blue + green
        glUniform3f(prog->getUniform("ka"), 0.2f, 0.2f, 0.2f);
        glUniform3f(prog->getUniform("kd"), 0.0f,0.0f,1.0f);
        glUniform3f(prog->getUniform("ks"), 0.0f, 1.0f, 0.0f);
        glUniform1f(prog->getUniform("s"), 200);
    }
    
    void mode1(){ // grey + low
        glUniform3f(prog->getUniform("ka"), 0.2f, 0.2f, 0.2f);
        glUniform3f(prog->getUniform("kd"), 0.5f,0.5f,0.5f);
        glUniform3f(prog->getUniform("ks"), 0.2f, 0.2f, 0.2f);
        glUniform1f(prog->getUniform("s"), 50);
    }
    
    void mode2(){ // lab7
        glUniform3f(prog->getUniform("ka"), 0.2f, 0.2f, 0.2f);
        glUniform3f(prog->getUniform("kd"), 0.8f, 0.7f, 0.7f);
        glUniform3f(prog->getUniform("ks"), 1.0f, 0.9f, 0.8f);
        glUniform1f(prog->getUniform("s"), 200);
    }
    
    void modeSil(){ // Silhouette
        glUniform3f(prog->getUniform("ka"), 0.2f, 0.2f, 0.2f);
        glUniform3f(prog->getUniform("kd"), 1.0f, 1.0f, 1.0f);
        glUniform3f(prog->getUniform("ks"), 1.0f, 1.0f, 1.0f);
        glUniform1f(prog->getUniform("s"), 200);
    }
};

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
	//keyToggles[key] = !keyToggles[key];
    switch (key) {
        case 109: // m
            --mode;
            break;
        case 77: // M
            ++mode;
            break;
        case 108: //l
            --lightsource;
            break;
        case 76: //L
            ++lightsource;
            break;
        case 120: //x
            L.modify_x(-0.05f, lightsource);
            break;
        case 88: // X
            L.modify_x(0.05f, lightsource);
            break;
        case 121: //y
            L.modify_y(-0.05f, lightsource);
            break;
        case 89: //Y
            L.modify_y(0.05f, lightsource);
        case 115: //s
            if (prog->getflag() == 1) {
                prog->setflag(2);
            }else{
                prog->setflag(1);
            }
            break;
        case 83: // S
            if (prog->getflag() == 1) {
                prog->setflag(2);
            }else{
                prog->setflag(1);
            }
            break;
        default:
            break;
    }
    if (mode > 2) {
        mode = 0;
    }else if (mode < 0){
        mode = 2;
    }
    
    if (lightsource < 1) {
        lightsource = 2;
    }else if (lightsource > 2){
        lightsource = 1;
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

	prog = make_shared<Program>();
	prog->setShaderNames(RESOURCE_DIR + "vert.glsl", RESOURCE_DIR + "frag.glsl", RESOURCE_DIR + "Silhouette.glsl");
	prog->setVerbose(true);
	prog->init();
	prog->addAttribute("aPos");
	prog->addAttribute("aNor");
	prog->addUniform("MV");
	prog->addUniform("P");
	prog->addUniform("lightPos");
    prog->addUniform("lightPos2");
	prog->addUniform("ka");
	prog->addUniform("kd");
	prog->addUniform("ks");
	prog->addUniform("s");
    prog->addUniform("intensity1");
    prog->addUniform("intensity2");
	prog->setVerbose(false);
	
	camera = make_shared<Camera>();
	camera->setInitDistance(2.0f);
	
	shape = make_shared<Shape>();
	//shape->loadMesh(RESOURCE_DIR + "bunny.obj");
    //shape->loadMesh(RESOURCE_DIR + "cube.obj");
    shape->loadMesh(input_obj);
	shape->fitToUnitBox();
	shape->init();
	
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
	
	prog->bind();
	glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
    
    glUniform3f(prog->getUniform("lightPos"), L.light1.x, L.light1.y, 1.0f);
    glUniform3f(prog->getUniform("lightPos2"), L.light2.x, L.light2.y, 1.0f);
    glUniform1f(prog->getUniform("intensity1"), 0.8f);
    glUniform1f(prog->getUniform("intensity2"), 0.2f);
    
    Material m;
    if (prog->getflag() == 1) {
        if (mode == 0) {
            m.mode0();
        }else if (mode == 1) {
            m.mode1();
        }else{
            m.mode2();
        }
    }else{
        m.modeSil();
    }
    
	shape->draw(prog);
	prog->unbind();
	
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
    input_obj = argv[2];
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
