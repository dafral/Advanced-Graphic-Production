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

}

void TransformWidget::update()
{
    if(w->currentEntity == nullptr) return;
    // Position
    ui->transX->setValue(w->currentEntity->transform.position.x);
    ui->transY->setValue(w->currentEntity->transform.position.y);
    // Scale
    ui->scaX->setValue(w->currentEntity->transform.scale.x);
    ui->scaY->setValue(w->currentEntity->transform.scale.y);
    // Name
    ui->label_entityName->setText(w->currentEntity->name);
    // Shape
    ui->comboBox_Shape->setCurrentIndex((int)w->currentEntity->shape);
    // Fill Color
    ui->spinBox_FillColor_R->setValue(w->currentEntity->fillColor.red());
    ui->spinBox_FillColor_G->setValue(w->currentEntity->fillColor.green());
    ui->spinBox_FillColor_B->setValue(w->currentEntity->fillColor.blue());
    // Fill Style
    ui->comboBox_FillStyle->setCurrentIndex((int)w->currentEntity->fillStyle);
    // Stroke Color
    ui->spinBox_StrokeColor_R->setValue(w->currentEntity->strokeColor.red());
    ui->spinBox_StrokeColor_G->setValue(w->currentEntity->strokeColor.green());
    ui->spinBox_StrokeColor_B->setValue(w->currentEntity->strokeColor.blue());
    // Stroke Thickness
    ui->spinBox_StrokeThicc->setValue(w->currentEntity->strokeThickness);
    // Stroke Style
    ui->comboBox_StrokeStyle->setCurrentIndex((int)w->currentEntity->strokeStyle);

}
