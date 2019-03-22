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
    //, ui(new Ui::InspectorWidget)
    //, transformWidget(nullptr)
{
    //ui->setupUi(this);
    //Create subwidgets independently
    transformWidget = new TransformWidget();
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

}

void InspectorWidget::ResetLayout()
{

}

InspectorWidget::~InspectorWidget()
{
    //delete ui;
}
