#ifndef HYERARCHYWIDGET_H
#define HYERARCHYWIDGET_H

#include <QWidget>
#include <list>
#include <QLabel>

#include "entity.h"

namespace Ui {
class HyerarchyWidget;
}

class HyerarchyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HyerarchyWidget(QWidget *parent = 0);
    ~HyerarchyWidget();

protected:
    Ui::HyerarchyWidget *ui;
    std::list<QLabel> labels;
public:
    void UpdateHyerarchy();
    void PaintHyerarchy();

    void CreateLabelFromEntity(Entity* ent);
    void CleanUpLabels();
};

#endif // HYERARCHYWIDGET_H
