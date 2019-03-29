#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inspectorwidget.h"
#include "customwidget.h"
#include "entity.h"

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class HyerarchyListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void AddEntity(Entity* ent);
    void DeleteEntity(Entity* ent);

    void UpdateInspector();

public slots:
    void openProject();
    void saveProject();
    void quit();

    void Update();

public:
    Ui::MainWindow *ui;
    InspectorWidget *uiInspector;
    CustomWidget *uiCustomWidget;
    HyerarchyListWidget* uiHyerarchy;

    //File manager
    QString pathtrunk;
    QString foldername;

public:
    QSettings settings;
    QList<Entity*> entities;
    Entity* currentEntity;

    bool quitApp;

};

extern MainWindow* w;

#endif // MAINWINDOW_H
