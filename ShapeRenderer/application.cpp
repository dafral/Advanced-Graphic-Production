#include "application.h"

App::App()
{

}
App::~App()
{

}

void App::CleanUp()
{
    for(int i = 0; i < entities.size(); ++i)
    {
        if(entities[i])
        {
            entities[i]->CleanUp();
            delete entities[i];
        }
    }
    entities.clear();
}
