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

    void Update();

    void AddEntity(Entity* ent);
    void DeleteEntity(Entity* ent);

public slots:
    void openProject();
    void saveProject();
    void quit();

private:
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

};

extern MainWindow* w;

#endif // MAINWINDOW_H
