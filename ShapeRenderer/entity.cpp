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
    fillStyle = Qt::BrushStyle::SolidPattern;

    //Pen properties
    strokeColor = QColor::fromRgb(0,0,0);
    strokeThickness = 4;
    strokeStyle = Qt::PenStyle::SolidLine;
}
