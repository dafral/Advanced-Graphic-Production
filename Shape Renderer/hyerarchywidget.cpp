#include "hyerarchywidget.h"
#include "ui_hyerarchywidget.h"

#include "application.h"

HyerarchyWidget::HyerarchyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HyerarchyWidget)
{
    ui->setupUi(this);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
}
HyerarchyWidget::~HyerarchyWidget()
{
    if(ui != nullptr)
        delete ui;
    CleanUpLabels();
}

void HyerarchyWidget::UpdateHyerarchy()
{
    CleanUpLabels();
    for(int i = 0; i < App.entities.size(); ++i)
    {
        CreateLabelFromEntity(App.entities[i]);
    }
}

void HyerarchyWidget::PaintHyerarchy()
{

}

void HyerarchyWidget::CreateLabelFromEntity(Entity *ent)
{
    if(ent == nullptr) return;

}

void HyerarchyWidget::CleanUpLabels()
{
    for(int i = 0; i < labels.size(); ++i)
    {
        if(labels != nullptr)
        {
            delete labels[i];
        }
    }
    labels.clear();
}


