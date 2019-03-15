#include "entity.h"
#include "mainwindow.h"

#include <QLabel>

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

void Entity::OnInspector(QVBoxLayout* layout)
{
    QLabel* labelName = new QLabel();
    labelName->setText(this->name);
    layout->addWidget(labelName);
}
