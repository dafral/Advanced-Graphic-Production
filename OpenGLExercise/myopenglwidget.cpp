#include "myopenglwidget.h"
#include "vertex.h"
#include "submesh.h"
#include "mesh.h"

#include <iostream>
#include <QOpenGLDebugLogger>

#pragma comment( lib, "OpenGL32.lib" )

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget (parent)
{
    setMinimumSize(QSize(256, 256));
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    makeCurrent();
    finalizeGL();
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    //Handle context destructions
    connect(context(), SIGNAL(aboutToBeDestroyed()),
            this, SLOT(finalizeGL()));

    if(context()->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
    {
        QOpenGLDebugLogger* logger = new QOpenGLDebugLogger(this);
        logger->initialize();
        connect(logger, SIGNAL(messageLogged(const QOpenGLDebugMessage &)),
                this, SLOT(handleLoggedMessage(const QOpenGLDebugMessage &)));
        logger->startLogging();
    }

    showInfo();

    // initializeTriangle();
    //initializeSphere();
    Mesh* mesh = initializeSphere();
    meshes.push_back(mesh);

}

void MyOpenGLWidget::handleLoggedMessage(const QOpenGLDebugMessage &debugMessage)
{
    std::cout << debugMessage.severity() << "!!: "
              << debugMessage.message().toStdString() << std::endl;
}

void MyOpenGLWidget::resizeGL(int width, int height)
{
    this->resize(width, height);
}

void MyOpenGLWidget::DrawMeshes()
{
    for(std::list<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it)
    {
        //(*it)->update();
        (*it)->draw();
    }
}

void MyOpenGLWidget::paintGL()
{

    glClearDepth(1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_CULL_FACE);

    DrawMeshes();

    /*if(program.bind())
    {
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vao.release();
        program.release();
    }*/
}

void MyOpenGLWidget::finalizeGL()
{
    std::cout << "finalize()" << std::endl;
}

void MyOpenGLWidget::showInfo()
{
    std::cout << "OpenGL version:" << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl << std::endl;

    std::cout << "OpenGL renderer:" << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl << std::endl;

    std::cout << "OpenGL vendor:" << std::endl;
    std::cout << glGetString(GL_VENDOR) << std::endl << std::endl;

    std::cout << "OpenGL GLSL version:" << std::endl;
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;

    std::cout << "OpenGL extensions:" << std::endl;
    GLint num_extensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
    for (int i = 0; i < num_extensions; ++i)
    {
        const unsigned char *str = glGetStringi(GL_EXTENSIONS, GLuint(i));
        std::cout << str << " ";
    }
    std::cout << std::endl;

    //Information about the surface format
    std::cout << context()->format().redBufferSize() << std::endl;
    std::cout << context()->format().greenBufferSize() << std::endl;
    std::cout << context()->format().blueBufferSize() << std::endl;
    std::cout << context()->format().alphaBufferSize() << std::endl;
    std::cout << context()->format().depthBufferSize() << std::endl;
}

Mesh* MyOpenGLWidget::CreateMesh()
{
    Mesh* newMesh = new Mesh();
    meshes.push_back(newMesh);
    return newMesh;
}

Mesh* MyOpenGLWidget::initializeCube()
{
    Mesh* mesh = new Mesh();
    QVector3D vertices[] = {
        QVector3D(-0.5f, -0.5f, 0.0f),
        QVector3D(-0.5f, 0.5f, 0.0f),
        QVector3D(0.5f, 0.5f, 0.0f),
        QVector3D(0.5f, -0.5f, 0.0f)
    };
    unsigned int indices[] = {
        0, 2, 1,
        0, 3, 2
    };

    VertexFormat vertexFormat;
    vertexFormat.setVertexAttribute(0, 0, 3);
    SubMesh* submesh = new SubMesh(vertexFormat, vertices, 4 * sizeof(QVector3D), indices, 6);
    mesh->submeshes.push_back(submesh);
    return mesh;
}

Mesh* MyOpenGLWidget::initializeTriangle()
{
    //Program
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/shader1.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/shader1.frag");
    program.link();
    program.bind();

    //VBO
    QVector3D vertices[] = {
        QVector3D(-0.5f, -0.5f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f), //Vertex 1
        QVector3D( 0.5f, -0.5f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f), //Vertex 2
        QVector3D( 0.0f,  0.5f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f)  //Vertex 3
    };

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices, 6 * sizeof(QVector3D));

    //VAO: Captures state of VBOs
    vao.create();
    vao.bind();
    const GLint compCount = 3;
    const int strideBytes = 2 * sizeof(QVector3D);
    const int offsetBytes0 = 0;
    const int offsetBytes1 = sizeof(QVector3D);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes0));
    glVertexAttribPointer(1, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes1));

    vao.release();
    program.release();
    vbo.release();

    return nullptr;
}

Mesh* MyOpenGLWidget::initializeSphere()
{
    //Program
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/3DShader.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/3DShader.frag");
    program.link();
    program.bind();

    Vertex sphere[H][V + 1];
    for(int i = 0; i < H; ++i)
    {
        for(int j = 0; j < V; ++j)
        {
            float nh = float(i) / H;
            float nv = float(j) / V - 0.5f;
            float angleh = 2 * pi * nh;
            float anglev = -pi * nv;

            sphere[i][j].pos.setX(sinf(angleh) * cosf(anglev));
            sphere[i][j].pos.setY(-sinf(anglev));
            sphere[i][j].pos.setZ(cosf(angleh) * cosf(anglev));
            sphere[i][j].norm = sphere[i][j].pos;
        }
    }
    unsigned int sphereIndices[H][V][6];
    for (unsigned int i = 0; i < H; ++i)
    {
        for (unsigned int j = 0; j < V; ++j)
        {
            sphereIndices[i][j][0] = (i+0)      * (V+1) + j;
            sphereIndices[i][j][1] = ((i+1)%H)  * (V+1) + j;
            sphereIndices[i][j][2] = ((i+1)%H)  * (V+1) + j+1;
            sphereIndices[i][j][3] = (i+0)      * (V+1) + j;
            sphereIndices[i][j][4] = ((i+1)%H)  * (V+1) + j+1;
            sphereIndices[i][j][5] = (i+0)      * (V+1) + j+1;
        }
    }
    VertexFormat vertexFormat;
    vertexFormat.setVertexAttribute(0,0,3);
    vertexFormat.setVertexAttribute(1, sizeof(QVector3D), 3);

    Mesh *mesh = this->CreateMesh();
    //mesh->name = "Sphere";

    QVector3D vertices[H * (V+1)];
    for(int i = 0; i < H; ++i)
    {
        for(int j = 0; j < V + 1; ++j)
        {
            vertices[i * j] = sphere[i][j].pos;
        }
    }

    mesh->addSubMesh(vertexFormat, vertices, sizeof(sphere), &sphereIndices[0][0][0], H*V*6);

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices, (H * (V + 1)) * sizeof(QVector3D));

    vao.create();
    vao.bind();
    const GLint compCount = 3;
    const int strideBytes = 2 * sizeof(QVector3D);
    const int offsetBytes0 = 0;
    const int offsetBytes1 = sizeof(QVector3D);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes0));
    glVertexAttribPointer(1, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes1));

    vao.release();
    program.release();
    vbo.release();

    return mesh;
}

void MyOpenGLWidget::CleanUpMeshes()
{
    for (std::list<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it)
    {
        if((*it) != nullptr)
            delete (*it);
    }
}

void MyOpenGLWidget::EnableVertexAttribArray(GLuint index)
{
    glEnableVertexAttribArray(index);
}

void MyOpenGLWidget::VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}


