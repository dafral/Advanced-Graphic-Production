#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "input.h"
#include "camera.h"

#include <iostream>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    running = true;

    ui->setupUi(this);

    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::TabPosition::North);

    //Create the inspector widget
    uiInspector = new InspectorWidget();
    ui->dockInspector->setWidget(uiInspector);

    //Create the circle widget
    uiCustomWidget = new CustomWidget();
    uiOpenGL = new MyOpenGLWidget();

    //Action triggers
    connect(ui->actionOpenProject, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->actionSaveProject, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(quit()));

    connect(ui->loadButton, SIGNAL(pressed()), this, SLOT(loadModel()));

    camera = new Camera();

    interaction = new Interaction();

    input = new Input();
    setMouseTracking(true);

    setFocus();
}

MainWindow::~MainWindow()
{
    SAFE_DELETE(camera);
    SAFE_DELETE(input);
    delete ui;
}

void MainWindow::loadModel()
{
    QString path = QFileDialog::getOpenFileName(this, "Load Model");
    if(!path.isEmpty())
    {
        std::cout << path.toStdString() << std::endl;
    }
    else
    {
        std::cout << "Error loading model -> empty path" << std::endl;
    }
    w->uiOpenGL->initialize3DModel(std::string(path.toStdString()).c_str());
}
void MainWindow::frame()
{
    // TODO
    /*bool interacted = interaction->update();
    if(interacted)
    {
        update();
        uiOpenGL->update();
    }
    input->postUpdate();
    */
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

void MainWindow::navigate()
{

}


void MainWindow::keyPressEvent(QKeyEvent* aEvent)
{
    input->keyPress(aEvent);
}
void MainWindow::keyReleaseEvent(QKeyEvent* aEvent)
{
    input->keyRelease(aEvent);
}
void MainWindow::mousePressEvent(QMouseEvent* aEvent)
{
    input->mousePress(aEvent);
}
void MainWindow::mouseReleaseEvent(QMouseEvent* aEvent)
{
    input->mouseRelease(aEvent);
}
void MainWindow::mouseMoveEvent(QMouseEvent* aEvent)
{
    input->mouseMove(aEvent);
}
