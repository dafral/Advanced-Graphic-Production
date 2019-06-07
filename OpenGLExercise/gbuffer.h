#ifndef GBUFFER_H
#define GBUFFER_H

#include <QOpenGLFunctions_3_3_Core>

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLDebugLogger>

#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

#define GBUFFER_POSITION_TEXTURE_UNIT 0
#define GBUFFER_DIFFUSE_TEXTURE_UNIT  1
#define GBUFFER_NORMAL_TEXTURE_UNIT   2
#define GBUFFER_TEXCOORD_TEXTURE_UNIT 3

class GBuffer
{
public:

    enum GBUFFER_TEXTURE_TYPE {
        GBUFFER_TETURE_TYPE_POSITION,
        GBUFFER_TETURE_TYPE_DIFUSE,
        GBUFFER_TETURE_TYPE_NORMAL,
        GBUFFER_TETURE_TYPE_TEXCOORD,
        GBUFFER_NUM_TEXTURES
    };

    GBuffer();

    ~GBuffer();

    bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
    void BindForWriting();
    void BindForReading();
    void SetReadBuffer(GBUFFER_TEXTURE_TYPE TextureType);

public:

    GLuint m_fbo;
    GLuint m_textures[GBUFFER_NUM_TEXTURES];
    GLuint m_depthTexture;
};

#endif // GBUFFER_H
