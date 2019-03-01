#ifndef HYERARCHYWIDGET_H
#define HYERARCHYWIDGET_H

#include <QWidget>
#include <vector>
#include <QLabel>
#include <QVBoxLayout>

#include "entity.h"
#include "entitylabel.h".h"

namespace Ui {
class Hyerarchy;
}

class HyerarchyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HyerarchyWidget(QWidget *parent = 0);
    ~HyerarchyWidget();

protected:
    Ui::Hyerarchy *ui;
    std::vector<EntityLabel*> labels;
    QVBoxLayout* layout;
public:
    void UpdateHyerarchy();
    void PaintHyerarchy();

    void CreateLabelFromEntity(Entity* ent);
    void CleanUpLabels();
};

#endif // HYERARCHYWIDGET_H
