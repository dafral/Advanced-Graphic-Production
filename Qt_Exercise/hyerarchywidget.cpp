#include "hyerarchywidget.h"
#include "ui_hyerarchywidget.h"

HyerarchyWidget::HyerarchyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HyerarchyWidget)
{
    ui->setupUi(this);
}

HyerarchyWidget::~HyerarchyWidget()
{
    delete ui;
}
