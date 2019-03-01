#include "entity.h"
#include "main.h"

virtual void Entity::Save()
{
    settings.beginGroup(name);

    settings.set("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}
