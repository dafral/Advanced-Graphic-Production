#ifndef HYERARCHYLISTWIDGET_H
#define HYERARCHYLISTWIDGET_H

#include <QWidget>

namespace Ui {
class HyerarchyListWidget;
}

class HyerarchyListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HyerarchyListWidget(QWidget *parent = 0);
    ~HyerarchyListWidget();

private:
    Ui::HyerarchyListWidget *ui;
};

#endif // HYERARCHYLISTWIDGET_H
