#ifndef ENTITYLABELWIDGET_H
#define ENTITYLABELWIDGET_H

#include <QWidget>
#include <string>
#include "entity.h"
#include <QLabel>

namespace Ui {
class EntityLabelWidget;
}

class EntityLabelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EntityLabelWidget(QWidget *parent = 0);
    explicit EntityLabelWidget(std::string str, QWidget *parent = 0);
    explicit EntityLabelWidget(std::string str, Entity* e, QWidget *parent = 0);
    ~EntityLabelWidget();

public:
    void PrintLabel();
    void CleanUp();
    Entity* GetEntity()
    {
        return entity;
    }
    QLabel* GetLabel()
    {
        return label;
    }

private:
    Ui::EntityLabelWidget *ui;
    Entity* entity;
    QLabel* label;
};

#endif // ENTITYLABELWIDGET_H
