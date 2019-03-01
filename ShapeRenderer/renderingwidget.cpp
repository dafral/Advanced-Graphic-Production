#include "renderingwidget.h"
#include "ui_rendering.h"
#include "mainwindow.h"

RenderingWidget::RenderingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderingWidget)
{
    ui->setupUi(this);
}

RenderingWidget::~RenderingWidget()
{
    delete ui;
}
