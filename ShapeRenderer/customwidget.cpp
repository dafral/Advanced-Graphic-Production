#include "customwidget.h"
#include "mainwindow.h"
#include "entity.h"

#include <iostream>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
}

QSize CustomWidget::sizeHint() const
{
    return QSize(256,256);
}

QSize CustomWidget::minimumSizeHint() const
{
    return QSize(64,64);
}

void CustomWidget::paintEvent(QPaintEvent *event)
{
    QColor blueColor = QColor::fromRgb(127,190,220);
    QColor whiteColor = QColor::fromRgb(255, 255, 255);
    QColor blackColor = QColor::fromRgb(0,0,0);

    //Prepare the painter for this widget
    QPainter painter(this);

    QBrush brush;
    QPen pen;

    //Brush/Pen configuration
    brush.setColor(blueColor);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    pen.setStyle(Qt::PenStyle::NoPen);
    painter.setBrush(brush);
    painter.setPen(pen);

    //Paint background
    //painter.drawRect(rect());
    for(int i = 0; i < w->entities.size(); i++)

    {
        //Brush/Pen configuration
        brush.setColor(w->entities[i]->fillColor);
        brush.setStyle(GetBrushStyle(w->entities[i]->fillStyle));
        pen.setWidth(w->entities[i]->strokeThickness);
        pen.setColor(w->entities[i]->strokeColor);
        pen.setStyle(GetPenStyle(w->entities[i]->strokeStyle));

        painter.setBrush(brush);
        painter.setPen(pen);

        QRectF shapeRect(w->entities[i]->transform.position.x, w->entities[i]->transform.position.y, w->entities[i]->transform.scale.x, w->entities[i]->transform.scale.y);
        //shapeRect.setX(w->entities[i]->transform.position.x);
        //shapeRect.setY(w->entities[i]->transform.position.y);
        //shapeRect.setWidth(w->entities[i]->transform.scale.x);
        //shapeRect.setHeight(w->entities[i]->transform.scale.y);

       switch(w->entities[i]->shape)
       {
           case Shape::Circle:
               painter.drawEllipse(shapeRect);
               break;

           case Shape::Square:
               painter.drawRect(shapeRect);
               break;
       }
    }
}

Qt::PenStyle CustomWidget::GetPenStyle(int pentype)
{
    switch (pentype) {
    case 0:
        return Qt::PenStyle::SolidLine;;
    case 1:
        return Qt::PenStyle::DashLine;
    case 2:
        return Qt::PenStyle::DotLine;
    case 3:
        return Qt::PenStyle::DashDotLine;
    case 4:
        return Qt::PenStyle::DashDotDotLine;
    }
}

Qt::BrushStyle CustomWidget::GetBrushStyle(int brushtype)
{
    switch (brushtype) {
    case 0:
        return Qt::BrushStyle::SolidPattern;
    case 1:
        return Qt::BrushStyle::Dense3Pattern;
    case 2:
        return Qt::BrushStyle::CrossPattern;
    case 3:
        return Qt::BrushStyle::LinearGradientPattern;
    case 4:
        return Qt::BrushStyle::NoBrush;
    }
}


