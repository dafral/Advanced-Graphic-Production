#include "entity.h"
#include "mainwindow.h"

Entity::Entity(QString n)
    : name(n)
{

}

void Entity::Save(QSettings* settings)
{
   settings->setValue("name", name);
}

void Entity::Load(QSettings* settings)
{
    //QSettings settings()
    //w->AddEntity(Entity* ent = new Entity());
}
