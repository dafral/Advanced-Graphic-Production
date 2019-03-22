#include "primitive.h"

#include <QPainter>

Primitive::Primitive()
{
    this->ResetValues();
}
Primitive::~Primitive()
{

}

void Primitive::ResetValues()
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

   // brush.setColor(static_cast<Primitive*>(w->entities[i])->fillColor);
   // brush.setStyle(static_cast<Primitive*>(w->entities[i])->fillStyle);
   // pen.setWidth(static_cast<Primitive*>(w->entities[i])->strokeThickness);
   // pen.setColor(static_cast<Primitive*>(w->entities[i])->strokeColor);
   // pen.setStyle(static_cast<Primitive*>(w->entities[i])->strokeStyle);

}

void Primitive::Save(QSettings* settings)
{

}

void Primitive::Load(QSettings* settings)
{

}
