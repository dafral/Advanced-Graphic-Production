#include "entity.h"
#include "mainwindow.h"

#include <QLabel>
#include <QPainter>

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

// Primitives //
void Entity::ResetPrimitiveValues()
{
    //Shape properties
    shape = Shape::Circle;

    //Brush properties
    fillColor = QColor::fromRgb(0,225,0);
    fillStyle = Qt::BrushStyle::SolidPattern;

    //Pen properties
    strokeColor = QColor::fromRgb(0,0,0);
    strokeThickness = 4;
    strokeStyle = Qt::PenStyle::SolidLine;
}
