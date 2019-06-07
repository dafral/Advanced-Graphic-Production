#include "dsgeometrypass.h"

#include <limits.h>
#include <string.h>
#include <QMatrix4x4>

DSGeometryPass::DSGeometryPass()
{

}

bool DSGeometryPass::Init()
{
    if(!ShaderManager::Init())
    {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "shaders/geometry_pass.fs"))
    {
        return false;
    }

    if (!Finalize())
    {
        return false;
    }

    m_WVPLocation = GetUniformLocation("gWVP");
    m_WorldMatrixLocation = GetUniformLocation("gWorld");
    m_colorTextureUnitLocation = GetUniformLocation("gColorMap");

    if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
        m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
        m_colorTextureUnitLocation == INVALID_UNIFORM_LOCATION)
    {
            return false;
    }

    return true;
}


void DSGeometryPass::SetWVP(const QMatrix4x4& WVP)
{
    gl->glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.data());
}


void DSGeometryPass::SetWorldMatrix(const QMatrix4x4& WorldInverse)
{
    gl->glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)WorldInverse.data());
}


void DSGeometryPass::SetColorTextureUnit(unsigned int TextureUnit)
{
    gl->glUniform1i(m_colorTextureUnitLocation, TextureUnit);
}

