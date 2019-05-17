#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QMessageBox>
#include <QFileDialog>

#include <QKeyEvent>

#include "input.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    cameraSpeed = 0.5f;
    running = true;

    ui->setupUi(this);

    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::TabPosition::North);

    //Create the inspector widget
    uiInspector = new InspectorWidget();
    ui->dockInspector->setWidget(uiInspector);

    //Create the circle widget
    uiCustomWidget = new CustomWidget();
    uiOpenGL = new MyOpenGLWidget();

    // [TODO] -> uncomment all "input"s
    //input = new p2Input();
    camera = new p2Camera();

    //Action triggers
    connect(ui->actionOpenProject, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->actionSaveProject, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(quit()));

    setMouseTracking(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(input == nullptr) return;
    input->keyPressEvent(event);

    w->update();
    w->uiOpenGL->update();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(input == nullptr) return;
    input->keyReleaseEvent(event);

    w->update();
    w->uiOpenGL->update();
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
        if(input == nullptr) return;
    input->mousePressEvent(event);

    w->update();
    w->uiOpenGL->update();
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
        if(input == nullptr) return;
    input->mouseReleaseEvent(event);

    w->update();
    w->uiOpenGL->update();
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
        if(input == nullptr) return;
    input->mouseMoveEvent(event);

    w->update();
    w->uiOpenGL->update();
}
void MainWindow::enterEvent(QEvent *event)
{
    grabKeyboard();
}
void MainWindow::leaveEvent(QEvent *event)
{
    releaseKeyboard();
}

void MainWindow::openProject()
{
    QString path = QFileDialog::getOpenFileName(this, "Open project");
    if(!path.isEmpty())
    {
        std::cout << path.toStdString() << std::endl;
    }
}

void MainWindow::saveProject()
{
    std::cout <<"Save project" << std::endl;
}

void MainWindow::quit()
{
    QMessageBox::StandardButton button = QMessageBox::question(
                this,
                "Exit application",
                "Do you want to exit the application without saving the project?");
    if(button == QMessageBox::Yes)
    {
        std::cout << "Exit without saving changes" << std::endl;
        qApp->exit();
    }

    else
    {
        std::cout << "Cancel exit" << std::endl;
    }


}
