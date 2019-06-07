#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <list>
#include <QOpenGLFunctions_3_3_Core>

class ShaderManager
{
public:
    ShaderManager();
    virtual ~ShaderManager();

    virtual bool Init();
    void Enable();

protected:

    bool AddShader(GLenum ShaderType, const char* pFilename);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);
    GLint GetProgramParam(GLint param);

    GLuint m_shaderProg;

private:

    typedef std::list<GLuint> ShaderObjList;
    ShaderObjList m_shaderObjList;
};

#endif // SHADERMANAGER_H
