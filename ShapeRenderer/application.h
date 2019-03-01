#ifndef APPLICATION_H
#define APPLICATION_H

#include "mainwindow.h"
#include "entity.h"

#include <vector>

class App
{
public:
    App();
    virtual ~App();
public:
    std::vector<Entity*> entities;
    MainWindow* w;

public:
    void CleanUp();
    MainWindow* CreateMainWindow();
}

extern App;

#endif // APPLICATION_H
