#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QMessageBox>
#include <QFileDialog>

#include "hyerarchylistwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::TabPosition::North);

    //Create the inspector widget
    uiInspector = new InspectorWidget();
    ui->dockInspector->setWidget(uiInspector);

    // Hyerarchy Widget //
    uiHyerarchy = new HyerarchyListWidget();
    ui->dockHierarchy->setWidget(uiHyerarchy);

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

void MainWindow::Update()
{
    uiInspector->Update();
}

void MainWindow::AddEntity(Entity *ent)
{
    if(ent == nullptr) return;
    uiHyerarchy->list->addItem(ent->GetName());
    entities.push_back(ent);
}
void MainWindow::DeleteEntity(Entity *ent)
{
    if(ent == nullptr) return;
    for(QList<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        if((*it) == ent)
        {
            entities.removeOne((*it));
            (*it)->CleanUp();
            if((*it) != nullptr)
                delete (*it);
        }
    }
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
        int size = settings.beginReadArray("entities");

        for(int i = 0; i < size; ++i)
        {
            settings.setArrayIndex(i);
            Entity* ent = new Entity();

            ent->name = settings.value("name").toString();

            std::cout << ent->name.toStdString() << std::endl;
            w->AddEntity(ent);
        }
        settings.endArray();
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
        settings.beginWriteArray("entities");

        for(int i = 0; i < entities.size(); i++)
        {
            settings.setArrayIndex(i);
            entities[i]->Save(&settings);
        }

        settings.endArray();
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
