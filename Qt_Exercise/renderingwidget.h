#ifndef RENDERINGWIDGET_H
#define RENDERINGWIDGET_H

#include <QWidget>

namespace Ui {
class RenderingWidget;
}

class RenderingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RenderingWidget(QWidget *parent = nullptr);
    ~RenderingWidget();

private:
    Ui::RenderingWidget *ui;
};

#endif // RENDERINGWIDGET_H
