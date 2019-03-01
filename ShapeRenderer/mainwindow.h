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

private:
    Ui::MainWindow *ui;
    InspectorWidget *uiInspector;
    CustomWidget *uiCustomWidget;

    //File manager
    QString pathtrunk;
    QString foldername;

public:
    QSettings settings;
    std::vector<Entity*> entities;

};

extern MainWindow* w;

#endif // MAINWINDOW_H
