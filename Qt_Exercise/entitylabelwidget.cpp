#include "entitylabelwidget.h"
#include "ui_entitylabelwidget.h"

EntityLabelWidget::EntityLabelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntityLabelWidget)
{
    ui->setupUi(this);
}

EntityLabelWidget::~EntityLabelWidget()
{
    delete ui;
}
