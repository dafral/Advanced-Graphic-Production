#include "shadermanager.h"
//#include "ogldev_util.h"
#include "myopenglwidget.h"

#include <stdio.h>
#include <string.h>

ShaderManager::ShaderManager()
{
    m_shaderProg = 0;
}


ShaderManager::~ShaderManager()
{
    // Delete the intermediate shader objects that have been added to the program
    // The list will only contain something if shaders were compiled but the object itself
    // was destroyed prior to linking.
    for (ShaderObjList::iterator it = m_shaderObjList.begin() ; it != m_shaderObjList.end() ; it++)
    {
        gl->glDeleteShader(*it);
    }

    if (m_shaderProg != 0)
    {
        gl->glDeleteProgram(m_shaderProg);
        m_shaderProg = 0;
    }
}


bool ShaderManager::Init()
{
    m_shaderProg = gl->glCreateProgram();

    if (m_shaderProg == 0) {
        fprintf(stderr, "Error creating shader program\n");
        return false;
    }

    return true;
}

// Use this method to add shaders to the program. When finished - call finalize()
bool ShaderManager::AddShader(GLenum ShaderType, const char* pFilename)
{
    std::string s;

    if (!ReadFile(pFilename, s)) {
        return false;
    }

    GLuint ShaderObj = gl->glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        return false;
    }

    // Save the shader object - will be deleted in the destructor
    m_shaderObjList.push_back(ShaderObj);

    const GLchar* p[1];
    p[0] = s.c_str();
    GLint Lengths[1] = { (GLint)s.size() };

    gl->glShaderSource(ShaderObj, 1, p, Lengths);

    gl->glCompileShader(ShaderObj);

    GLint success;
    gl->glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar InfoLog[1024];
        gl->glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling '%s': '%s'\n", pFilename, InfoLog);
        return false;
    }

    gl->glAttachShader(m_shaderProg, ShaderObj);

    return true;
}


// After all the shaders have been added to the program call this function
// to link and validate the program.
bool ShaderManager::Finalize()
{
    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    gl->glLinkProgram(m_shaderProg);

    gl->glGetProgramiv(m_shaderProg, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        gl->glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        return false;
    }

    gl->glValidateProgram(m_shaderProg);
    gl->glGetProgramiv(m_shaderProg, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        gl->glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
     //   return false;
    }

    // Delete the intermediate shader objects that have been added to the program
    for (ShaderObjList::iterator it = m_shaderObjList.begin() ; it != m_shaderObjList.end() ; it++) {
        gl->glDeleteShader(*it);
    }

    m_shaderObjList.clear();

    return GLCheckError();
}


void ShaderManager::Enable()
{
    gl->glUseProgram(m_shaderProg);
}


GLint ShaderManager::GetUniformLocation(const char* pUniformName)
{
    GLuint Location = gl->glGetUniformLocation(m_shaderProg, pUniformName);

    if (Location == INVALID_UNIFORM_LOCATION) {
        fprintf(stderr, "Warning! Unable to get the location of uniform '%s'\n", pUniformName);
    }

    return Location;
}

GLint ShaderManager::GetProgramParam(GLint param)
{
    GLint ret;
    gl->glGetProgramiv(m_shaderProg, param, &ret);
    return ret;
}
