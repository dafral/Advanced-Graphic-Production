#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>

#include "hyerarchylistwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    quitApp(false)
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

    // Update Timer //
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer->start(10);

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

void MainWindow::UpdateInspector()
{
    uiInspector->transformWidget->update();
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
        if((*it) == ent && ent != nullptr)
        {
            if((*it) != nullptr)
            {
               delete (*it);
            }
            entities.removeOne((*it));
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
            Entity* ent = new Entity("noname");

            //Loading name & transform
            ent->name = settings.value("name").toString();

            ent->transform.position.x = settings.value("x").toFloat();
            ent->transform.position.y = settings.value("y").toFloat();

            ent->transform.scale.x = settings.value("width").toFloat();
            ent->transform.scale.y = settings.value("height").toFloat();

            //Saving shape properties
            //ent->shape = settings.value("shape").toInt();
            switch(settings.value("shape").toInt())
            {
            case 0:
                ent->shape = Shape::Empty;
                break;

            case 1:
                ent->shape = Shape::Circle;
                break;

            case 2:
                ent->shape = Shape::Square;
                break;

            case 3:
                ent->shape = Shape::Infinite;
                break;
            }

            int fill_r, fill_g, fill_b, stroke_r, stroke_g, stroke_b;

            fill_r = settings.value("fillcolor_r").toInt();
            fill_g = settings.value("fillcolor_g").toInt();
            fill_b = settings.value("fillcolor_b").toInt();
            ent->fillColor = QColor::fromRgb(fill_r, fill_g, fill_b);
            //ent->fillstyle = settings.value("fillstyle").toInt();

            stroke_r= settings.value("strokecolor_r").toInt();
            stroke_g= settings.value("strokecolor_g").toInt();
            stroke_b= settings.value("strokecolor_b").toInt();
            ent->strokeColor = QColor::fromRgb(stroke_r, stroke_g, stroke_b);
            //ent->strokeStyle = settings.value("strokestyle").toInt();
            ent->strokeThickness = settings.value("strokethickness").toFloat();

            std::cout << ent->strokeStyle << std::endl;
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
        quitApp = true;
        qApp->exit();
    }

    else
    {
        std::cout << "Cancel exit" << std::endl;
    }


}
