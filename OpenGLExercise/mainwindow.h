#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inspectorwidget.h"
#include "customwidget.h"
#include "myopenglwidget.h"
#include <QMainWindow>
#include "input.h"
#include "camera.h"
#include "interaction.h"

#define SAFE_DELETE(x) if(x != nullptr) delete x;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openProject();
    void saveProject();
    void quit();

    void loadModel();

public:
    Ui::MainWindow *ui;
    InspectorWidget *uiInspector;
    CustomWidget *uiCustomWidget;
    MyOpenGLWidget *uiOpenGL;

    Camera *camera;

    Interaction *interaction;

    Input *input;

    bool running;

public slots:
    void frame();

public:
    void navigate();

    void keyPressEvent(QKeyEvent* aEvent);
    void keyReleaseEvent(QKeyEvent* aEvent);
    void mousePressEvent(QMouseEvent* aEvent);
    void mouseReleaseEvent(QMouseEvent* aEvent);
    void mouseMoveEvent(QMouseEvent* aEvent);

};
extern MainWindow* w;

#endif // MAINWINDOW_H
