#include "customwidget.h"
#include "mainwindow.h"

#include <QPainter>
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
        std::cout << "entra en el for" << std::endl;

        //Brush/Pen configuration
        brush.setColor(w->entities[i]->fillColor);
        brush.setStyle(w->entities[i]->fillStyle);
        pen.setWidth(w->entities[i]->strokeThickness);
        pen.setColor(w->entities[i]->strokeColor);
        pen.setStyle(w->entities[i]->strokeStyle);

        painter.setBrush(brush);
        painter.setPen(pen);

        //Draw circle
        int r = 64;
        int w = r * 2;
        int h = r * 2;
        int x = rect().width()/2 - r;
        int y = rect().height()/2 - r;
        QRect circleRect(x, y, w, h);
        painter.drawEllipse(circleRect);
    }

}
