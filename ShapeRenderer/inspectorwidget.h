#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H

#include <QWidget>
#include "entity.h"

#include "inspectorwidget.h"
#include "transformwidget.h"
#include "renderingwidget.h"

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
    void ResetLayout();
private:
    Ui::InspectorWidget *ui;
    Entity* currentEntity;
    QVBoxLayout* layout;
public:
    TransformWidget* transformWidget;
};

#endif // INSPECTORWIDGET_H
