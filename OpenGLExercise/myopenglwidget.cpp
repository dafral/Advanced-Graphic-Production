#include "myopenglwidget.h"
#include "vertex.h"
#include "submesh.h"
#include "mesh.h"

#include <iostream>
#include <QOpenGLDebugLogger>
#include <QOpenGLFramebufferObject>
#include <QOpenGLTexture>

#include "mainwindow.h"

#pragma comment( lib, "OpenGL32.lib" )

QOpenGLFunctions_3_3_Core *gl = nullptr;

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget (parent)
{
    setMinimumSize(QSize(256, 256));
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    makeCurrent();
    finalizeGL();
    CleanUpMeshes();
}

void MyOpenGLWidget::initializeGL()
{
    gl = this;
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

    if(!m_gbuffer.Init(width(), height()))
    {
        std::cout << "Error loading GBuffer!" << std::endl;
    }

    if (!m_DSGeometryPass.Init()) {
        printf("Error initializing DSGeomPassTech\n");
    }

    m_DSGeometryPass.Enable();
    m_DSGeometryPass.SetColorTextureUnit(COLOR_TEXTURE_UNIT_INDEX);

    glEnable(GL_DEPTH_TEST);

    connect(&timer, SIGNAL(timeout()), this, SLOT(frame()));
    if(format().swapInterval() == -1)
    {
        timer.setInterval(17);
    }
    else
    {
        timer.setInterval(0);
    }
    timer.start();

    //Shaders
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/3DShader.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/3DShader.frag");
    program.link();

    showInfo();

    //initializeTriangle();
    //initializeSphere();
    //initializeCube();
    initialize3DModel("Resources/StoneFloor/StoneFloor.obj");

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

void MyOpenGLWidget::paintGL()
{
    //gl->glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    UpdateMeshes();

    w->camera->prepareMatrices();

    glClearDepth(1.0f);
    glClearColor(0.4f, 0.4f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_CULL_FACE);

    UseShader();
    DrawMeshes();

    QOpenGLFramebufferObject::bindDefault();

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
    w->uiOpenGL->meshes.push_back(newMesh);
    return newMesh;
}

void MyOpenGLWidget::UpdateMeshes()
{
    for (std::list<Mesh*>::iterator it = w->uiOpenGL->meshes.begin(); it != w->uiOpenGL->meshes.end(); ++it)
    {
         if((*it)->needsUpdate)
         {
             (*it)->update();
             (*it)->needsUpdate = false;
         }
    }
}

void MyOpenGLWidget::DrawMeshes()
{
    for (std::list<Mesh*>::iterator it = w->uiOpenGL->meshes.begin(); it != w->uiOpenGL->meshes.end(); ++it)
    {
        (*it)->draw();
    }
}

void MyOpenGLWidget::UseShader()
{
    if(program.bind())
    {
        /*// Projection transformation
        QMatrix4x4 projectionMatrix;
        const float fovy = 60.0f;
        const float aspectRatio = (float)width() / (float)height();
        const float znear = 0.1;
        const float zfar = 1000.0;
        projectionMatrix.perspective(fovy, aspectRatio, znear, zfar);

        // Camera transformation
        QMatrix4x4 viewMatrix;
        QVector3D eyePosition(5.0, 5.0, 10.0);
        QVector3D center(0.0, 0.0, 0.0);
        QVector3D up(0.0, 1.0, 0.0);
        viewMatrix.lookAt(eyePosition, center, up);*/

        // Object transformation
        QMatrix4x4 worldMatrix;
        QMatrix4x4 worldViewMatrix = w->camera->viewMatrix * worldMatrix;

        program.setUniformValue("projectionMatrix", w->camera->projectionMatrix);
        program.setUniformValue("worldViewMatrix", worldViewMatrix);

        for(auto it = w->uiOpenGL->meshes.begin(); it != w->uiOpenGL->meshes.end(); ++it)
        {
            if((*it) != nullptr)
            {
                if((*it)->diffuse != nullptr)
                {
                    (*it)->diffuse->textureId();
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, (*it)->diffuse->textureId());
                    program.setUniformValue("diffuse_tex", 0);
                    program.setUniformValue("activeDiffuse", (*it)->activateDiffuse);
                }
                else
                {
                    program.setUniformValue("activeDiffuse", 0);
                }
                if((*it)->normalMap != nullptr)
                {
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, (*it)->normalMap->textureId());
                    program.setUniformValue("normalMap", 1);
                    program.setUniformValue("activeNormalMap", (*it)->activateNormalMap);
                }
                else
                {
                    program.setUniformValue("activeNormalMap", 0);
                }
            }
        }

    }
}



void MyOpenGLWidget::initializeCube()
{
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

    Mesh *mesh = this->CreateMesh();
    //mesh->name = "Cube";
    mesh->addSubMesh(vertexFormat, vertices, sizeof(vertices), indices, sizeof(indices));
    mesh->needsUpdate = true;
}

void MyOpenGLWidget::frame()
{
    bool interacted = w->interaction->update();
    if(interacted)
    {
        update();
    }
    w->input->postUpdate();
}

Mesh* MyOpenGLWidget::initializeTriangle()
{
    /*
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
*/
    return nullptr;
}

void MyOpenGLWidget::initializeSphere()
{

    Vertex sphere[H][V + 1];
    for(int i = 0; i < H; ++i)
    {
        for(int j = 0; j < V + 1; ++j)
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
        for (unsigned int j = 0; j < V + 1; ++j)
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
    mesh->addSubMesh(vertexFormat, sphere, sizeof(sphere), &sphereIndices[0][0][0], H*V*6);
    mesh->needsUpdate = true;
}

void MyOpenGLWidget::initialize3DModel(const char* filename)
{
    Mesh *mesh = this->CreateMesh();
    //mesh->name = filename;
    std::cout << "file -> " << filename << std::endl;
    mesh->loadModel(filename);
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


