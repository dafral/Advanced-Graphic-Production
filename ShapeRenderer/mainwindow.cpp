#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::TabPosition::North);

    //Create the inspector widget
    uiInspector = new InspectorWidget();
    ui->dockInspector->setWidget(uiInspector);

    //Create the circle widget
    uiCustomWidget = new CustomWidget();

    //Action triggers
    connect(ui->actionOpenProject, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->actionSaveProject, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(quit()));

    //Create scenes folder
    pathtrunk = QString("");
    foldername = QString("Scenes");

    QDir(pathtrunk).mkdir(foldername);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openProject()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open project"), "", tr("scene(*.sce);;All files(*)"));

    if(fileName.isEmpty())
    {
        std::cout << "Error. File name is empty!" << std::endl;
        return;
    }

    else
    {
        std::cout << fileName.toStdString() << std::endl;

        QSettings settings(fileName, QSettings::IniFormat);

        settings.beginGroup("MainWindow");
        resize(settings.value("size", QSize(400, 400)).toSize());
        move(settings.value("pos", QPoint(200, 200)).toPoint());
        settings.endGroup();

    }
}

void MainWindow::saveProject()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Scene"), "", tr("Scene (*.sce);;All Files (*)"));

    if(fileName.isEmpty())
    {
        std::cout << "Error. File name is empty!" << std::endl;
        return;
    }

    else
    {
        std::cout << fileName.toStdString() << std::endl;

        QSettings settings(fileName, QSettings::IniFormat);

        settings.beginGroup("MainWindow");
        settings.setValue("size", size());
        settings.setValue("pos", pos());
        settings.endGroup();
    }
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
