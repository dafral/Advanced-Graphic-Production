#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QWidget>
#include "entity.h"

namespace Ui {
class TransformWidget;
}

class TransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransformWidget(QWidget *parent = nullptr);
    ~TransformWidget();

public slots:
    void OnGUIChanged();

private:
    Ui::TransformWidget *ui;
    Entity* auxCurrEntity;
public:
    void Update();
    void update();
};


#endif // TRANSFORMWIDGET_H
