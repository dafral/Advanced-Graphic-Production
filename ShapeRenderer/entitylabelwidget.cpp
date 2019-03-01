#include "entitylabelwidget.h"
#include "ui_entitylabelwidget.h"

EntityLabelWidget::EntityLabelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntityLabelWidget)
{
    ui->setupUi(this);
}
EntityLabelWidget::EntityLabelWidget(std::string str, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntityLabelWidget)
{
    ui->setupUi(this);
    label = new QLabel(str.c_str());
    entity = nullptr;
}
EntityLabelWidget::EntityLabelWidget(std::string str, Entity* e, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntityLabelWidget)
{
    ui->setupUi(this);
    label = new QLabel(str.c_str());
    entity = e;
}

EntityLabelWidget::~EntityLabelWidget()
{
    delete ui;
}

void EntityLabelWidget::PrintLabel()
{

}

void EntityLabelWidget::CleanUp()
{
    if(label != nullptr)
    {
        delete label;
    }
}
