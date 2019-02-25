#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H


#include <QWidget>

namespace Ui {
class InspectorWidget;
}

class InspectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    ~InspectorWidget();

private:
    Ui::InspectorWidget *ui;
};

#endif // INSPECTORWIDGET_H
