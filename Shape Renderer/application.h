#ifndef APPLICATION_H
#define APPLICATION_H

#include <list>

#include "entity.h"

class Application
{
public:
    Application();
    virtual ~Application();
public:
    std::list<Entity*> entities;
public:
    void CleanUp();
}

static Application;
typedef Application App;

#endif // APPLICATION_H
