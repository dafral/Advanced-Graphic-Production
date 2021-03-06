#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inspectorwidget.h"
#include "customwidget.h"
#include <QMainWindow>

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

};

#endif // MAINWINDOW_H
