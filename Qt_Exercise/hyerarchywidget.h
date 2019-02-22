#ifndef HYERARCHYWIDGET_H
#define HYERARCHYWIDGET_H

#include <QWidget>

namespace Ui {
class HyerarchyWidget;
}

class HyerarchyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HyerarchyWidget(QWidget *parent = 0);
    ~HyerarchyWidget();

private:
    Ui::HyerarchyWidget *ui;
};

#endif // HYERARCHYWIDGET_H
