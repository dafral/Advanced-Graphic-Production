#include "transformwidget.h"
#include "ui_transformwidget.h"
#include "mainwindow.h"

TransformWidget::TransformWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformWidget)
{
    ui->setupUi(this);
}

TransformWidget::~TransformWidget()
{
    delete ui;
}

void TransformWidget::Update()
{
    if(w->currentEntity == nullptr) return;
    ui->transX->setValue(w->currentEntity->transform.position.x);
    ui->transY->setValue(w->currentEntity->transform.position.y);
    ui->transZ->setValue(w->currentEntity->transform.position.z);
}
