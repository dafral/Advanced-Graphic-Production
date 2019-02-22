#include "application.h"

Application::Application()
{

}
Application::~Application()
{

}

Application::CleanUp()
{
    for(int i = 0; i < entities.size(); ++i)
    {
        if(entities[i] != nullptr)
        {
            entities[i].CleanUp();
            delete entities[i];
        }
    }
    entities.clear();
}
