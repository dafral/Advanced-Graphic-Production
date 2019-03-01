#include "myopenglwidget.h"
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

    drawTriangle();

}

void MyOpenGLWidget::handleLoggedMessage(const QOpenGLDebugMessage &debugMessage)
{
    std::cout << debugMessage.severity() << "!!: "
              << debugMessage.message().toStdString() << std::endl;
}

void MyOpenGLWidget::resizeGL(int width, int height)
{
    //TODO: resize textures
}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.9f, 0.85f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
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

void MyOpenGLWidget::drawTriangle()
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

    //Release
    if(program.bind())
    {
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vbo.release();
        program.release();
    }


}
