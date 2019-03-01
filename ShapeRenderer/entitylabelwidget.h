#ifndef ENTITYLABELWIDGET_H
#define ENTITYLABELWIDGET_H

#include <QWidget>

namespace Ui {
class EntityLabelWidget;
}

class EntityLabelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EntityLabelWidget(QWidget *parent = 0);
    ~EntityLabelWidget();

private:
    Ui::EntityLabelWidget *ui;
};

#endif // ENTITYLABELWIDGET_H
