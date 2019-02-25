#include "inspectorwidget.h"
#include "transformwidget.h"
#include "renderingwidget.h"

#include <QLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

InspectorWidget::InspectorWidget(QWidget *parent) :
    QWidget (parent)
{
    //Create subwidgets independently
    TransformWidget *transformWidget = new TransformWidget;
    RenderingWidget *renderingWidget = new RenderingWidget;
    QSpacerItem *spacer = new QSpacerItem(1,1,QSizePolicy::Expanding, QSizePolicy::Expanding);

    //Create a vertical layour for this widget
    QVBoxLayout *layout = new QVBoxLayout;

    //Add all the elements to the layout
    layout->addWidget(transformWidget);
    layout->addWidget(renderingWidget);
    layout->addItem(spacer);

    //Set the layout for this widget
    setLayout(layout);
}

InspectorWidget::~InspectorWidget()
{
    //delete ui;
}
