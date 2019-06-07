#include "dsgeometrypass.h"

#include <limits.h>
#include <string.h>

DSGeometryPass::DSGeometryPass()
{

}

bool DSGeometryPass::Init()
{
    if(!ShaderObject::Init())
    {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "shaders/geometry_pass.fs")) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }

    m_WVPLocation = GetUniformLocation("gWVP");
    m_WorldMatrixLocation = GetUniformLocation("gWorld");
    m_colorTextureUnitLocation = GetUniformLocation("gColorMap");

    if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
        m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
        m_colorTextureUnitLocation == INVALID_UNIFORM_LOCATION) {
            return false;
    }

    return true;
}


void DSGeomPassTech::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}


void DSGeomPassTech::SetWorldMatrix(const Matrix4f& WorldInverse)
{
    glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)WorldInverse.m);
}


void DSGeomPassTech::SetColorTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(m_colorTextureUnitLocation, TextureUnit);
}

