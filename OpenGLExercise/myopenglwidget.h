#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QOpenGLDebugLogger>

#include "gbuffer.h"
#include "dsgeometrypass.h"
#include "mesh.h"

// TEXTURES
#define COLOR_TEXTURE_UNIT              GL_TEXTURE0
#define COLOR_TEXTURE_UNIT_INDEX        0

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

private:
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;

    std::list<Mesh*> meshes;
    QTimer timer;

    GBuffer m_gbuffer;
    DSGeometryPass m_DSGeometryPass;
};

extern QOpenGLFunctions_3_3_Core* gl;

#endif // MYOPENGLWIDGET_H
