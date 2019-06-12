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
    , QuadVAO(0)
    , QuadVBO(0)
{
    setMinimumSize(QSize(256, 256));
    lightDirection = QVector3D(0, 0, 1);
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    makeCurrent();
    finalizeGL();
    CleanUpMeshes();
}

void MyOpenGLWidget::InitGBuffer()
{
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    // pos
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, NULL, GL_RGB16F, width(), height(), 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

    // normals
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->width(), this->height(), 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

    // albedo
    glGenTextures(1, &gAlbedo);
    glBindTexture(GL_TEXTURE_2D, gAlbedo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width(), this->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);

    // specular
    glGenTextures(1, &gSpecular);
    glBindTexture(GL_TEXTURE_2D, gSpecular);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->width(), this->height(), 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, gSpecular, 0);

    unsigned int attachments[4] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
    glDrawBuffers(4, attachments);

    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->width(), this->height());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
         std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    lightingProg.bind();
    glUniform1i(glGetUniformLocation(lightingProg.programId(),"gPosition"),0);
    glUniform1i(glGetUniformLocation(lightingProg.programId(),"gNormal"),1);
    glUniform1i(glGetUniformLocation(lightingProg.programId(),"gAlbedo"),2);
    glUniform1i(glGetUniformLocation(lightingProg.programId(), "gSpecular"), 3);

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
    lightingProg.create();
    lightingProg.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/lighting.vert");
    lightingProg.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/lighting.frag");
    lightingProg.link();

    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/geometry.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/geometry.frag");
    program.link();

    hdrProg.create();
    hdrProg.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/hdr.vert");
    hdrProg.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/hdr.frag");
    hdrProg.link();

    InitGBuffer();

    glGenFramebuffers(1, &gHDR);
    glBindFramebuffer(GL_FRAMEBUFFER, gHDR);
    hdrProg.bind();
    glUniform1i(glGetUniformLocation(hdrProg.programId(),"hdrBuffer"),0);

    showInfo();

    //initializeTriangle();
    //initializeSphere();
    //initializeCube();
    initialize3DModel("Resources/Patrick/Patrick.obj");

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

    //w->camera->prepareMatrices();

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glDisable(GL_CULL_FACE);

    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    UseShader();
    DrawMeshes();

    QOpenGLFramebufferObject::bindDefault();
    // use geo shader
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //UseShader();
    //DrawMeshes();
    //QOpenGLFramebufferObject::bindDefault();

    //Use lightning shader
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_ONE,GL_ONE);
    //glDepthMask(false);
    UseLightingShader();
    //Render quad
    RenderQuad();

    glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0,0, this->width(), this->height(), 0,0,this->width(), this->height(), GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //Use HDR shader
    glUniform1i(glGetUniformLocation(hdrProg.programId(),"hdr"), activateHDR);
    glUniform1f(glGetUniformLocation(hdrProg.programId(),"exposure"), exposureHDR);
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
        if((*it)->diffuse != nullptr && (*it)->activateDiffuse == 1)
        {
            diffuse = glGetUniformLocation(program.programId(), "diffuseTex");
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, (*it)->diffuse->textureId());
            glUniform1i(diffuse, 0);
        }
        else
        {
            (*it)->activateDiffuse = 0;
        }
        if((*it)->normalMap != nullptr && (*it)->activateNormalMap == 1)
        {
            normal = glGetUniformLocation(program.programId(), "normalMap");
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, (*it)->normalMap->textureId());
            glUniform1i(normal, 1);
        }
        else
        {
            (*it)->activateNormalMap = 0;
        }

        glUniform1i(glGetUniformLocation(program.programId(), "diffuseEnabled"), (*it)->activateDiffuse);
        glUniform1i(glGetUniformLocation(program.programId(), "normalEnabled"), (*it)->activateNormalMap);
        glUniform1i(glGetUniformLocation(program.programId(), "specularEnabled"), (*it)->activateSpecular);

        QMatrix4x4 modelMatrix;
        modelMatrix.setToIdentity();
        modelMatrix.translate((*it)->position);
        modelMatrix.scale((*it)->scale);
        modelMatrix.rotate((*it)->rotation.x(), QVector3D(1, 0, 0));
        modelMatrix.rotate((*it)->rotation.y(), QVector3D(0, 1, 0));
        modelMatrix.rotate((*it)->rotation.z(), QVector3D(0, 0, 1));

        program.setUniformValue("modelMatrix", modelMatrix);

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

        w->camera->prepareMatrices();

        program.setUniformValue("projectionMatrix", w->camera->projectionMatrix);
        program.setUniformValue("viewMatrix", w->camera->viewMatrix);

        glUniform1f(glGetUniformLocation(program.programId(), "viewPosX"), w->camera->position.x());
        glUniform1f(glGetUniformLocation(program.programId(), "viewPosY"), w->camera->position.y());
        glUniform1f(glGetUniformLocation(program.programId(), "viewPosZ"), w->camera->position.z());

        std::cout << "L: " << w->uiOpenGL->lightDirection.x() << " - " << w->uiOpenGL->lightDirection.y() << " - " << w->uiOpenGL->lightDirection.z() << std::endl;

        glUniform1f(glGetUniformLocation(program.programId(), "Lx"), w->uiOpenGL->lightDirection.x());
        glUniform1f(glGetUniformLocation(program.programId(), "Ly"), w->uiOpenGL->lightDirection.y());
        glUniform1f(glGetUniformLocation(program.programId(), "Lz"), w->uiOpenGL->lightDirection.z());

        /*glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);

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

*/

    }
}

void MyOpenGLWidget::UseLightingShader()
{
    if(lightingProg.bind())
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gAlbedo);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, gSpecular);

        glUniform1f(glGetUniformLocation(lightingProg.programId(), "Lx"), w->uiOpenGL->lightDirection.x());
        glUniform1f(glGetUniformLocation(lightingProg.programId(), "Ly"), w->uiOpenGL->lightDirection.y());
        glUniform1f(glGetUniformLocation(lightingProg.programId(), "Lz"), w->uiOpenGL->lightDirection.z());

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

void MyOpenGLWidget::RenderQuad()
{
    if(QuadVAO == 0)
    {
        float QuadV[] = {
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1,&QuadVAO);
        glGenBuffers(1, &QuadVBO);
        glBindVertexArray(QuadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, QuadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(QuadV), &QuadV, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 5*sizeof(float), (void*)(3 * sizeof (float)));

    }
    gl->glBindVertexArray(QuadVAO);
    gl->glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
    gl->glBindVertexArray(0);
}


