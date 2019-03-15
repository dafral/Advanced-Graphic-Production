#include "hyerarchylistwidget.h"
#include "ui_hyerarchylistwidget.h"

HyerarchyListWidget::HyerarchyListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HyerarchyListWidget)
{
    ui->setupUi(this);
}

HyerarchyListWidget::~HyerarchyListWidget()
{
    delete ui;
}
