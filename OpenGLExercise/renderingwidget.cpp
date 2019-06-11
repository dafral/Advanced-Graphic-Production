#include "renderingwidget.h"
#include "ui_rendering.h"
#include "mainwindow.h"

RenderingWidget::RenderingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderingWidget)
{
    ui->setupUi(this);

    //Deferred checkboxes
    connect(ui->boxDiffuseR, SIGNAL(clicked(bool)), this, SLOT(SwitchRDiffuse()));
    connect(ui->boxNormalsR, SIGNAL(clicked(bool)), this, SLOT(SwitchRNormals()));
    connect(ui->boxSpecularR, SIGNAL(clicked(bool)), this, SLOT(SwitchRSpecular()));

    //Shaders checkboxes
    connect(ui->boxNormalMapping, SIGNAL(clicked(bool)), this, SLOT(SwitchNormalMapping()));
    connect(ui->boxHDR, SIGNAL(clicked(bool)), this, SLOT(SwitchHDR()));
    connect(ui->boxBloom, SIGNAL(clicked(bool)), this, SLOT(SwitchBloom()));
}

RenderingWidget::~RenderingWidget()
{
    delete ui;
}

void RenderingWidget::SwitchRDiffuse()
{

}

void RenderingWidget::SwitchRNormals()
{

}

void RenderingWidget::SwitchRSpecular()
{

}

void RenderingWidget::SwitchNormalMapping()
{

}

void RenderingWidget::SwitchHDR()
{

}

void RenderingWidget::SwitchBloom()
{

}
