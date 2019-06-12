#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QOpenGLDebugLogger>

#include "mesh.h"

// Sphere //
#define H 32
#define V 16

class MyOpenGLWidget :
        public QOpenGLWidget,
        public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget *parent = nullptr);
    ~MyOpenGLWidget() override;

    //From these methods we can call OpenGL function
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    void showInfo();

    // Meshes //
    Mesh* CreateMesh();
    void UpdateMeshes();
    void DrawMeshes();
    void CleanUpMeshes();

    void InitGBuffer();

    Mesh* initializeTriangle();
    void initializeSphere();
    void initializeCube();
    void initialize3DModel(const char* filename);

    void UseShader();

    void EnableVertexAttribArray(GLuint index);
    void VertexAttribPointer(GLuint index,
                             GLint size,
                             GLenum type,
                             GLboolean normalized,
                             GLsizei stride,
                             const GLvoid * pointer);

signals:
    void messageLogged(const QOpenGLDebugMessage &);

public slots:
    void frame();
    //Not virtual
    void finalizeGL();
    void handleLoggedMessage(const QOpenGLDebugMessage &);

public:
    std::list<Mesh*> meshes;
    QVector3D lightDirection;

    bool changed = false;

private:
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;
    QOpenGLShaderProgram lightingProg;
    QOpenGLShaderProgram hdrProg;

    QTimer timer;

    unsigned int gBuffer;
    unsigned int gAlbedo;
    unsigned int gNormal;
    unsigned int gPosition;
    unsigned int gSpecular;
    unsigned int gHDR;

    //HDR
    int activateHDR = 0;
    float exposureHDR = 2.5f;

    GLuint diffuse;
    GLuint normal;

    void UseLightingShader();

    void RenderQuad();
    unsigned int QuadVAO = 0;
    unsigned int QuadVBO = 0;

};

extern QOpenGLFunctions_3_3_Core* gl;

#endif // MYOPENGLWIDGET_H
