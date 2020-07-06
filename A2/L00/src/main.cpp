#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLSL.h"
#include "MatrixStack.h"
#include "Program.h"
#include "Shape.h"


using namespace std;

GLFWwindow *window; // Main application window
string RES_DIR = ""; // Where data files live
shared_ptr<Program> prog;
shared_ptr<Shape> shape;
string flag = "";
int numx = 0;
int numy = 0;
int numz = 0;
int choice = 0;
vector<vector<int>> v(11,vector<int> (3,0));

static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

static void init()
{
	GLSL::checkVersion();

	// Set background color.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);

	// Initialize mesh.
	shape = make_shared<Shape>();
	shape->loadMesh(RES_DIR + "cube.obj");
	shape->init();
	
	// Initialize the GLSL program.
	prog = make_shared<Program>();
	prog->setVerbose(true);
	prog->setShaderNames(RES_DIR + "simple_vert.glsl", RES_DIR + "simple_frag.glsl");
	prog->init();
	prog->addUniform("P");
	prog->addUniform("MV");
	prog->addAttribute("aPos");
	prog->addAttribute("aNor");
	prog->setVerbose(false);
	
	// If there were any OpenGL errors, this will print something.
	// You can intersperse this line in your code to find the exact location
	// of your OpenGL error.
	GLSL::checkError(GET_FILE_LINE);
}

static void render()
{
	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float aspect = width/(float)height;
	glViewport(0, 0, width, height);

	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Create matrix stacks.
	auto P = make_shared<MatrixStack>();
	//auto MV = make_shared<MatrixStack>();
    MatrixStack MV;
	// Apply projection.
	
    P->pushMatrix();
    P->multMatrix(glm::perspective((float)(45.0*M_PI/180.0), aspect, 0.01f, 100.0f));
	// Apply camera transform.
    
    MV.pushMatrix();
        MV.translate(0, 1, -8);
        MV.rotate(10.0*v[0][0]*M_PI/180.0, 1, 0, 0);
        MV.rotate(10.0*v[0][1]*M_PI/180.0, 0, 1, 0);
        MV.rotate(10.0*v[0][2]*M_PI/180.0, 0, 0, 1);
    
        MV.pushMatrix();
        MV.rotate(10.0*v[1][0]*M_PI/180.0, 1, 0, 0);
        MV.rotate(10.0*v[1][1]*M_PI/180.0, 0, 1, 0);
        MV.rotate(10.0*v[1][2]*M_PI/180.0, 0, 0, 1);
        if (choice == 1) {
            MV.scale(1.1, 2.2, 1.1);
        }else{
            MV.scale(1, 2, 1);
        }
        prog->bind();
        glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &P->topMatrix()[0][0]);
        glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, &MV.topMatrix()[0][0]);
        shape->draw(prog);
        prog->unbind();
        MV.popMatrix();
    
        MV.pushMatrix();
            MV.translate(0, 1, 0);
            MV.rotate(10.0*v[2][0]*M_PI/180.0, 1, 0, 0);
            MV.rotate(10.0*v[2][1]*M_PI/180.0, 0, 1, 0);
            MV.rotate(10.0*v[2][2]*M_PI/180.0, 0, 0, 1);
            MV.pushMatrix();
                MV.translate(0, 0.25, 0);
                if (choice == 2) {
                    MV.scale(0.55, 0.55, 0.55);
                }else{
                    MV.scale(0.5, 0.5, 0.5);
                }
                prog->bind();
                glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &P->topMatrix()[0][0]);
                glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, &MV.topMatrix()[0][0]);
                shape->draw(prog);
                prog->unbind();
            MV.popMatrix();
        MV.popMatrix();
        for (int i = 0; i <= 6; i+=2) {
            MV.pushMatrix();
            if (i==0) {
                MV.translate(0.5, 0.6, 0);
            }else if (i == 2){
                MV.translate(-0.5, 0.6, 0);
            }else if (i == 4){
                MV.translate(0.25, -1, 0);
            }else {
                MV.translate(-0.25, -1, 0);
            }
                MV.rotate(10.0*v[3+i][0]*M_PI/180.0, 1, 0, 0);
                MV.rotate(10.0*v[3+i][1]*M_PI/180.0, 0, 1, 0);
                MV.rotate(10.0*v[3+i][2]*M_PI/180.0, 0, 0, 1);
            MV.pushMatrix();
                if (i == 0) {
                    MV.translate(0.5, 0, 0);
                }else if (i == 2){
                    MV.translate(-0.5, 0, 0);
                }else if (i == 4){
                    MV.translate(0, -0.75, 0);
                }else{
                    MV.translate(0, -0.75, 0);
                }
                if (i <= 2) {
                    if (choice == 3+i) {
                        MV.scale(1.1, 0.55, 0.55);
                    }else{
                        MV.scale(1, 0.5, 0.5);
                    }
                }else{
                    if (choice == 3+i) {
                        MV.scale(0.495, 1.65, 0.495);
                    }else{
                        MV.scale(0.45, 1.5, 0.45);
                    }
                }
                prog->bind();
                glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &P->topMatrix()[0][0]);
                glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, &MV.topMatrix()[0][0]);
                shape->draw(prog);
                prog->unbind();
            MV.popMatrix();
            MV.pushMatrix();
                if (i == 0) {
                    MV.translate(1, 0, 0);
                }else if (i == 2){
                    MV.translate(-1, 0, 0);
                }else{
                    MV.translate(0, -1.5, 0);
                }
                MV.rotate(10.0*v[4+i][0]*M_PI/180.0, 1, 0, 0);
                MV.rotate(10.0*v[4+i][1]*M_PI/180.0, 0, 1, 0);
                MV.rotate(10.0*v[4+i][2]*M_PI/180.0, 0, 0, 1);
                MV.pushMatrix();
                    if (i == 0) {
                        MV.translate(0.5, 0, 0);
                    }else if (i == 2){
                        MV.translate(-0.5, 0, 0);
                    }else{
                        MV.translate(0, -0.65, 0);
                    }
                    if (i <= 2) {
                        if (choice == 4+i) {
                            MV.scale(1.1, 0.385, 0.385);
                        }else{
                            MV.scale(1, 0.35, 0.35);
                        }
                    }else{
                        if (choice == 4+i) {
                            MV.scale(0.4455, 1.43, 0.4455);
                        }else{
                            MV.scale(0.405, 1.3, 0.405);
                        }
                    }
                    prog->bind();
                    glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &P->topMatrix()[0][0]);
                    glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, &MV.topMatrix()[0][0]);
                    shape->draw(prog);
                    prog->unbind();
                MV.popMatrix();
            MV.popMatrix();
        MV.popMatrix();
        }
    MV.popMatrix();
    
    P->popMatrix();
    
	GLSL::checkError(GET_FILE_LINE);
}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
    if (choice > 10) {
        choice = 0;
    }
    switch (codepoint) {
        case 120:
            ++v[choice][0];
            break;
        case 88:
            --v[choice][0];
            break;
        case 121:
            ++v[choice][1];
            break;
        case 89:
            --v[choice][1];
            break;
        case 122:
            ++v[choice][2];
            break;
        case 90:
            --v[choice][2];
            break;
        case 44:
            --choice;
            break;
        case 46:
            ++choice;
            break;
        default:
            break;
    }
    if (choice < 0) {
        choice = 0;
    }
}

int main(int argc, char **argv)
{
	if(argc < 2) {
		cout << "Please specify the resource directory." << endl;
		return 0;
	}
	RES_DIR = argv[1] + string("/");

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
	// Set vsync.
	glfwSwapInterval(1);
	// Set keyboard callback.
	glfwSetKeyCallback(window, key_callback);
	// Initialize scene.
	init();
    // Set keyboard character callback
    glfwSetCharCallback(window, character_callback);
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
