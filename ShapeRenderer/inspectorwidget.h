#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H

#include <QWidget>
#include "entity.h"

namespace Ui {
class InspectorWidget;
}

class InspectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    ~InspectorWidget();
    void Update();

private:
    Ui::InspectorWidget *ui;
    Entity* currentEntity;
    QVBoxLayout* layout;
};

#endif // INSPECTORWIDGET_H
