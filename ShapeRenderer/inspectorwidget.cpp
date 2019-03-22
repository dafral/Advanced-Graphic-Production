#include "inspectorwidget.h"
#include "transformwidget.h"
#include "renderingwidget.h"

#include "mainwindow.h"
#include "entity.h"

#include <QLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>

InspectorWidget::InspectorWidget(QWidget *parent) :
    QWidget (parent)
{
    //Create subwidgets independently
    TransformWidget* transformWidget = new TransformWidget();
    //RenderingWidget *renderingWidget = new RenderingWidget();
    QSpacerItem *spacer = new QSpacerItem(1,1,QSizePolicy::Expanding, QSizePolicy::Expanding);

    //Create a vertical layour for this widget
    layout = new QVBoxLayout();

    //Add all the elements to the layout
    layout->addWidget(transformWidget);
    //layout->addWidget(renderingWidget);
    layout->addItem(spacer);

    //Set the layout for this widget
    setLayout(layout);
}

void InspectorWidget::Update()
{
    //if(transformWidget != nullptr)
    //{
    //    transformWidget->Update();
    //}
    if(w->currentEntity == nullptr) return;
    ResetLayout();
    /*if(currentEntity != w->currentEntity)
    {
        if(layout != nullptr)
        {
            layout->
            delete layout;
        }
        layout = new QVBoxLayout();
        currentEntity = w->currentEntity;
        currentEntity->OnInspector(layout);
        setLayout(layout);
    }*/
}

void InspectorWidget::ResetLayout()
{
    if(layout == nullptr) return;
    for(int i = 0; i < layout->count(); ++i)
    {
        layout->removeItem(layout->itemAt(i));
    }
    delete layout;
    layout = new QVBoxLayout();
    setLayout(layout);
}

InspectorWidget::~InspectorWidget()
{
    //delete ui;
}
