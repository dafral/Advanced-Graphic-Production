#ifndef ENTITYLABEL_H
#define ENTITYLABEL_H

#include <QPushButton>
#include "entity.h"

class EntityLabel : public QPushButton
{
public:
    EntityLabel();
    virtual ~EntityLabel();
public:
    Entity* ent;
};

#endif // ENTITYLABEL_H
