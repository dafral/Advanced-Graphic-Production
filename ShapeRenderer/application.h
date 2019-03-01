#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include "entity.h"

class App
{
public:
    App();
    virtual ~App();
public:
    std::vector<Entity*> entities;
public:
    void CleanUp();
}

static App;

#endif // APPLICATION_H
