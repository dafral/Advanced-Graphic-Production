#include "renderingwidget.h"
#include "ui_rendering.h"
#include "mainwindow.h"

RenderingWidget::RenderingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderingWidget)
{
    ui->setupUi(this);

    activeDiff = true;
    activeNormal = true;
    activeSpecular = true;

    //Deferred checkboxes
    ui->boxDiffuseR->setChecked(true);
    ui->boxNormalsR->setChecked(true);
    ui->boxSpecularR->setChecked(true);
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
    this->activeDiff = !activeDiff;
    for(auto it = w->uiOpenGL->meshes.begin(); it != w->uiOpenGL->meshes.end(); ++it)
    {
        if((*it) != nullptr)
        {
            (*it)->activateDiffuse = this->activeDiff;
        }
    }
}

void RenderingWidget::SwitchRNormals()
{
    activeNormal = !activeNormal;
    for(auto it = w->uiOpenGL->meshes.begin(); it != w->uiOpenGL->meshes.end(); ++it)
    {
        if((*it) != nullptr)
        {
            (*it)->activateNormalMap = this->activeNormal;
        }
    }
}

void RenderingWidget::SwitchRSpecular()
{
    this->activeSpecular = !activeSpecular;
    for(auto it = w->uiOpenGL->meshes.begin(); it != w->uiOpenGL->meshes.end(); ++it)
    {
        if((*it) != nullptr)
        {
            (*it)->activateSpecular = this->activeSpecular;
        }
    }
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
