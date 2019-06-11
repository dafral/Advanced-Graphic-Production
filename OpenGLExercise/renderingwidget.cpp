#include "renderingwidget.h"
#include "ui_rendering.h"
#include "mainwindow.h"

RenderingWidget::RenderingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderingWidget)
{
    ui->setupUi(this);

    //Deferred checkboxes
    connect(ui->boxDiffuseR, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->boxNormalsR, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(ui->boxSpecularR, SIGNAL(triggered()), this, SLOT(quit()));

    //Shaders checkboxes
    connect(ui->boxNormalMapping, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->boxHDR, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->boxBloom, SIGNAL(triggered()), this, SLOT(openProject()));
}

RenderingWidget::~RenderingWidget()
{
    delete ui;
}
