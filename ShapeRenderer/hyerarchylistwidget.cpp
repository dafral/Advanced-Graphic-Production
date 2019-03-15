#include "hyerarchylistwidget.h"
#include "ui_hyerarchylistwidget.h"

#include "mainwindow.h"
#include "entity.h"

HyerarchyListWidget::HyerarchyListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HyerarchyListWidget)
{
    ui->setupUi(this);
    list = ui->listWidget;
    connect(ui->buttonAddEntity, SIGNAL(clicked()), this, SLOT(OnAddEntity()));
    connect(ui->buttonDeleteEntity, SIGNAL(clicked()), this, SLOT(OnDeleteEntity()));

    // 4 very purposes serious //
    entityNames.push_back("Popentity Pupuntity");
    entityNames.push_back("enTITIS");
    entityNames.push_back("Entity");
    entityNames.push_back("Daventity Franciskity Frankity");
    entityNames.push_back("Jason Momoa");
    entityNames.push_back("John Centity");
    entityNames.push_back("Hippity Hoppity u r now my Entity");
    entityNames.push_back("Manasuel");
    entityNames.push_back("Raúl el Listo");

}

HyerarchyListWidget::~HyerarchyListWidget()
{
    delete ui;
}

// Slots //
void HyerarchyListWidget::OnAddEntity()
{
    QString auxName = "Entity";
    auxName.append(QString::number(w->entities.size()));
    if(rand() % 100 > 90) auxName = entityNames[rand() % entityNames.size()];
    Entity* ent = new Entity(auxName);
    list->addItem(ent->GetName());
    w->AddEntity(ent);
}
void HyerarchyListWidget::OnDeleteEntity()
{
    if(list->currentRow() == -1) return;
    list->takeItem(list->currentRow());
    w->DeleteEntity(w->entities.at(list->currentRow()));
}
