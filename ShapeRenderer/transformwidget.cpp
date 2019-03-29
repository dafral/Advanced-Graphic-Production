#include "transformwidget.h"
#include "ui_transformwidget.h"
#include "mainwindow.h"

TransformWidget::TransformWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformWidget)
{
    ui->setupUi(this);

    // Pos
    connect(ui->transX, SIGNAL(valueChanged(double)), this, SLOT(OnGUIChanged()));
    connect(ui->transY, SIGNAL(valueChanged(double)), this, SLOT(OnGUIChanged()));
    // Sca
    connect(ui->scaX, SIGNAL(valueChanged(double)), this, SLOT(OnGUIChanged()));
    connect(ui->scaY, SIGNAL(valueChanged(double)), this, SLOT(OnGUIChanged()));
    // Name
    connect(ui->label_entityName, SIGNAL(textChanged(QString)), this, SLOT(OnGUIChanged()));
    // Shape
    connect(ui->comboBox_Shape, SIGNAL(currentIndexChanged(int)), this, SLOT(OnGUIChanged()));
    // Fill Color
    connect(ui->spinBox_FillColor_R, SIGNAL(valueChanged(double)), this, SLOT(OnGUIChanged()));
    connect(ui->spinBox_FillColor_G, SIGNAL(valueChanged(double)), this, SLOT(OnGUIChanged()));
    connect(ui->spinBox_FillColor_B, SIGNAL(valueChanged(double)), this, SLOT(OnGUIChanged()));
    // Fill Style
    connect(ui->comboBox_FillStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(OnGUIChanged()));
    // Stroke Color
    connect(ui->spinBox_StrokeColor_R, SIGNAL(valueChanged(double)), this, SLOT(OnGUIChanged()));
    connect(ui->spinBox_StrokeColor_G, SIGNAL(valueChanged(double)), this, SLOT(OnGUIChanged()));
    connect(ui->spinBox_StrokeColor_B, SIGNAL(valueChanged(double)), this, SLOT(OnGUIChanged()));
    // Stroke Thicc
    connect(ui->spinBox_StrokeThicc, SIGNAL(valueChanged(double)), this, SLOT(OnGUIChanged()));
    // Stroke Style
    connect(ui->comboBox_StrokeStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(OnGUIChanged()));

}

TransformWidget::~TransformWidget()
{
    delete ui;
}

// SLOTS //
void TransformWidget::OnGUIChanged()
{
    if(w->currentEntity == nullptr) return;
    // Sets //
    // Position
    w->currentEntity->transform.position.x = ui->transX->value();
    w->currentEntity->transform.position.y = ui->transY->value();
    // Scale
    w->currentEntity->transform.scale.x = ui->scaX->value();
    w->currentEntity->transform.scale.y = ui->scaY->value();
    // Name
    w->currentEntity->name = ui->label_entityName->text();
    // Shape
    w->currentEntity->shape = (Shape)ui->comboBox_Shape->currentIndex();
    // Fill Color
    w->currentEntity->fillColor.setRed(ui->spinBox_FillColor_R->value());
    w->currentEntity->fillColor.setGreen(ui->spinBox_FillColor_G->value());
    w->currentEntity->fillColor.setBlue(ui->spinBox_FillColor_B->value());
    // Fill Style
    w->currentEntity->fillStyle = (Fill)ui->comboBox_FillStyle->currentIndex();
    // Stroke Color
    w->currentEntity->strokeColor.setRed(ui->spinBox_StrokeColor_R->value());
    w->currentEntity->strokeColor.setGreen(ui->spinBox_StrokeColor_G->value());
    w->currentEntity->strokeColor.setBlue(ui->spinBox_StrokeColor_B->value());
    // Stroke Thickness
    w->currentEntity->strokeThickness = ui->spinBox_StrokeThicc->value();
    // Stroke Style
    w->currentEntity->strokeStyle = (Stroke)ui->comboBox_StrokeStyle->currentIndex();
}

// UPDATE //
void TransformWidget::Update()
{

}

void TransformWidget::update()
{
    if(w->currentEntity == nullptr) return;

    // Update //
    if(auxCurrEntity != w->currentEntity)
    {
        auxCurrEntity = w->currentEntity;

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
}
