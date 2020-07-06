#include "Program.h"

#include <iostream>
#include <cassert>

#include "GLSL.h"

using namespace std;

Program::Program() :
	vShaderName(""),
	fShaderName(""),
	pid(0),
	verbose(true)
{
	
}

Program::~Program()
{
	
}

void Program::setShaderNames(const string &v, const string &f, const string &s)
{
	vShaderName = v;
	fShaderName = f;
    sShaderName = s;
}

bool Program::init()
{
	GLint rc;
	
	// Create shader handles
	GLuint VS = glCreateShader(GL_VERTEX_SHADER);
	GLuint FS = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint SS = glCreateShader(GL_FRAGMENT_SHADER);
    
	// Read shader sources
	const char *vshader = GLSL::textFileRead(vShaderName.c_str());
	const char *fshader = GLSL::textFileRead(fShaderName.c_str());
    const char *sshader = GLSL::textFileRead(sShaderName.c_str());
	
    glShaderSource(VS, 1, &vshader, NULL);
	glShaderSource(FS, 1, &fshader, NULL);
	glShaderSource(SS, 1, &sshader, NULL);
    
	// Compile vertex shader
	glCompileShader(VS);
	glGetShaderiv(VS, GL_COMPILE_STATUS, &rc);
	if(!rc) {
		if(isVerbose()) {
			GLSL::printShaderInfoLog(VS);
			cout << "Error compiling vertex shader " << vShaderName << endl;
		}
		return false;
	}
	
	// Compile fragment shader
	glCompileShader(FS);
	glGetShaderiv(FS, GL_COMPILE_STATUS, &rc);
	if(!rc) {
		if(isVerbose()) {
			GLSL::printShaderInfoLog(FS);
			cout << "Error compiling fragment shader " << fShaderName << endl;
		}
		return false;
	}
    
    glCompileShader(SS);
    glGetShaderiv(SS, GL_COMPILE_STATUS, &rc);
    if(!rc) {
        if(isVerbose()) {
            GLSL::printShaderInfoLog(SS);
            cout << "Error compiling fragment shader " << fShaderName << endl;
        }
        return false;
    }
	
	// Create the program and link
	pid = glCreateProgram();
    pid2 = glCreateProgram();
	
    glAttachShader(pid, VS);
	glAttachShader(pid, FS);
	glLinkProgram(pid);
	glGetProgramiv(pid, GL_LINK_STATUS, &rc);
	if(!rc) {
		if(isVerbose()) {
			GLSL::printProgramInfoLog(pid);
			cout << "Error linking shaders " << vShaderName << " and " << fShaderName << endl;
		}
		return false;
	}
    
    glAttachShader(pid2, VS);
    glAttachShader(pid2, SS);
    glLinkProgram(pid2);
    glGetProgramiv(pid2, GL_LINK_STATUS, &rc);
    if(!rc) {
        if(isVerbose()) {
            GLSL::printProgramInfoLog(pid2);
            cout << "Error linking shaders " << vShaderName << " and " << fShaderName << endl;
        }
        return false;
    }
	
	GLSL::checkError(GET_FILE_LINE);
	return true;
}

void Program::bind()
{
    if (flag == 1) {
        glUseProgram(pid);
    }else{
        glUseProgram(pid2);
    }
}

void Program::unbind()
{
	glUseProgram(0);
}

void Program::setflag(int shaderChoice){
    flag = shaderChoice;
}

int Program::getflag(){
    return flag;
}

void Program::addAttribute(const string &name)
{
    if (flag == 1) {
        attributes[name] = glGetAttribLocation(pid, name.c_str());
    }else{
        attributes[name] = glGetAttribLocation(pid2, name.c_str());
    }
	
}

void Program::addUniform(const string &name)
{
    if (flag == 1) {
        uniforms[name] = glGetUniformLocation(pid, name.c_str());
    }else{
        uniforms[name] = glGetUniformLocation(pid2, name.c_str());
    }
}

GLint Program::getAttribute(const string &name) const
{
	map<string,GLint>::const_iterator attribute = attributes.find(name.c_str());
	if(attribute == attributes.end()) {
		if(isVerbose()) {
			cout << name << " is not an attribute variable" << endl;
		}
		return -1;
	}
	return attribute->second;
}

GLint Program::getUniform(const string &name) const
{
	map<string,GLint>::const_iterator uniform = uniforms.find(name.c_str());
	if(uniform == uniforms.end()) {
		if(isVerbose()) {
			cout << name << " is not a uniform variable" << endl;
		}
		return -1;
	}
	return uniform->second;
}
