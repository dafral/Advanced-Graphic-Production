#include "hyerarchywidget.h"
#include "ui_hyerarchywidget.h"

#include "application.h"
#include "entitylabelwidget.h"

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

void HyerarchyWidget::CreateLabelFromEntity(Entity *ent)
{
    if(ent == nullptr) return;
    labels.push_back(new EntityLabelWidget(ent->name, ent));
    layout->addWidget(labels[labels.size() - 1]);
}

void HyerarchyWidget::CleanUpLabels()
{
    for(int i = 0; i < labels.size(); ++i)
    {
        if(labels[i] != nullptr)
        {
            labels[i]->CleanUp();
            delete labels[i];
        }
    }
    labels.clear();
}


