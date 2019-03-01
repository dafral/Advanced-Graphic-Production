#include "mainwindow.h"
#include "application.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App* app = new App();

    app->CreateMainWindow();

    app->w.show();

    return a.exec();
}
