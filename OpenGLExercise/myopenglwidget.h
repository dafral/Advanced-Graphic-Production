#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLDebugLogger>

class MyOpenGLWidget :
        public QOpenGLWidget,
        protected QOpenGLFunctions_3_3_Core
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

    void initializeTriangle();
    void initializeSphere(int h, int v);

signals:
    void messageLogged(const QOpenGLDebugMessage &);

public slots:

    //Not virtual
    void finalizeGL();
    void handleLoggedMessage(const QOpenGLDebugMessage &);

private:
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;

};

#endif // MYOPENGLWIDGET_H
