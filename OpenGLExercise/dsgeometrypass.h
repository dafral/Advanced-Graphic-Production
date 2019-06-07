#ifndef DSGEOMETRYPASS_H
#define DSGEOMETRYPASS_H

#include "shadermanager.h"
#include "myopenglwidget.h"
#include <QMatrix4x4>

class DSGeometryPass : public ShaderManager
{
public:
    DSGeometryPass();

    virtual bool Init();

    void SetWVP(const QMatrix4x4& WVP);
    void SetWorldMatrix(const QMatrix4x4& WorldInverse);
    void SetColorTextureUnit(unsigned int TextureUnit);

private:

    GLuint m_WVPLocation;
    GLuint m_WorldMatrixLocation;
    GLuint m_colorTextureUnitLocation;
};

#endif // DSGEOMETRYPASS_H
