#include "entity.h"
#include "mainwindow.h"

#include <QLabel>

Entity::Entity(QString n)
    : name(n)
{

}

Entity::~Entity()
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

void Entity::OnInspector(QVBoxLayout* layout)
{
    QLabel* labelName = new QLabel();
    labelName->setText(this->name);
    layout->addWidget(labelName);
}
