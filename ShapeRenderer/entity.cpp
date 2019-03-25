#include "entity.h"
#include "mainwindow.h"

#include <QLabel>
#include <QPainter>
#include <iostream>

Entity::Entity(QString n)
    : name(n)
{
    this->ResetPrimitiveValues();
}

Entity::~Entity()
{

}

void Entity::Save(QSettings* settings)
{
   //Saving name & transform
   settings->setValue("name", name);

   settings->setValue("x", transform.position.x);
   settings->setValue("y", transform.position.y);

   settings->setValue("width", transform.scale.x);
   settings->setValue("height", transform.scale.y);

   //Saving shape properties
   settings->setValue("shape", shape);

   settings->setValue("fillcolor_r", fillColor.red());
   settings->setValue("fillcolor_g", fillColor.green());
   settings->setValue("fillcolor_b", fillColor.blue());
   settings->setValue("fillstyle", fillStyle);

   settings->setValue("strokecolor_r", strokeColor.red());
   settings->setValue("strokecolor_g", strokeColor.green());
   settings->setValue("strokecolor_b", strokeColor.blue());
   settings->setValue("strokestyle", strokeStyle);
   settings->setValue("strokethickness", strokeThickness);
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

// Primitives //
void Entity::ResetPrimitiveValues()
{
    //Transform properties
    //int x = rect().width()/2 - r;
    //int y = rect().height()/2 - r;
    transform.position.x = 0;
    transform.position.y = 0;
    transform.scale.x = 128;
    transform.scale.y = 128;

    //Shape properties
    shape = Shape::Circle;

    //Brush properties
    fillColor = QColor::fromRgb(0,225,0);
    fillStyle = Fill::Gradient;

    //Pen properties
    strokeColor = QColor::fromRgb(0,0,0);
    strokeThickness = 4;
    strokeStyle = Stroke::Dot;
}
