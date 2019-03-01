#include "hyerarchywidget.h"
#include "ui_hyerarchywidget.h"

#include "application.h"
#include "entitylabelwidget.h"
#include "entitylabel.h"

HyerarchyWidget::HyerarchyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hyerarchy)
{
    ui->setupUi(this);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    layout = new QVBoxLayout();
}
HyerarchyWidget::~HyerarchyWidget()
{
    if(ui != nullptr)
        delete ui;
    if(layout != nullptr)
        delete layout;
    CleanUpLabels();
}

void HyerarchyWidget::UpdateHyerarchy()
{
    CleanUpLabels();
    for(int i = 0; i < App.entities.size(); ++i)
    {
        if(App.entities[i] != nullptr)
        {
            CreateLabelFromEntity(App.entities[i]);
        }
    }
    setLayout(layout);
}

void HyerarchyWidget::PaintHyerarchy()
{
    this->show();
}

void HyerarchyWidget::CreateLabelFromEntity(Entity *e)
{
    if(e == nullptr) return;
    EntityLabel* el = new EntityLabel();
    el->ent = e;
    el->setText(e->name);
    labels.push_back(el);
    layout->addWidget(el);
}

void HyerarchyWidget::CleanUpLabels()
{
    for(int i = 0; i < labels.size(); ++i)
    {
        if(labels[i] != nullptr)
        {
            delete labels[i];
        }
    }
    labels.clear();
}


