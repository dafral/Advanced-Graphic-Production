#include "entity.h"
#include "mainwindow.h"

Entity::Entity(QString n)
    : name(n)
{

}

void Entity::Save()
{
    //w->settings.beginGroup((QString)name);

   // settings.set("size", size());
   // settings.setValue("pos", pos());
   // settings.endGroup();
}
