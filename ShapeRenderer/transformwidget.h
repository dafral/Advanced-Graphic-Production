#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QWidget>

namespace Ui {
class TransformWidget;
}

class TransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransformWidget(QWidget *parent = nullptr);
    ~TransformWidget();

private:
    Ui::TransformWidget *ui;
public:
    void Update();
    void update();
};


#endif // TRANSFORMWIDGET_H
