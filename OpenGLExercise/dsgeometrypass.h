#ifndef DSGEOMETRYPASS_H
#define DSGEOMETRYPASS_H

#include "shaderobject.h"


class DSGeometryPass : public ShaderObject
{
public:
    DSGeometryPass();

    virtual bool Init();

    void SetWVP(const QMatrix4x4& WVP);
    void SetWorldMatrix(const QMatrix4x4& WVP);
    void SetColorTextureUnit(unsigned int TextureUnit);

private:

    GLuint m_WVPLocation;
    GLuint m_WorldMatrixLocation;
    GLuint m_colorTextureUnitLocation;
};

#endif // DSGEOMETRYPASS_H
