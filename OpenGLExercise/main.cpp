#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

MainWindow* w = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setMinorVersion(3);
    format.setMajorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setOption(QSurfaceFormat::DebugContext);
    QSurfaceFormat::setDefaultFormat(format);

    w = new MainWindow();
    w->setFocus();
    w->show();

    if(!w->running)
    {
        delete w;
    }

    return a.exec();
}
