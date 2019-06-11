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

public slots:
    void SwitchRNormals();
    void SwitchRDiffuse();
    void SwitchRSpecular();
    void SwitchNormalMapping();
    void SwitchHDR();
    void SwitchBloom();

private:
    Ui::RenderingWidget *ui;

    bool activeDiff;
    bool activeNormal;
    bool activeSpecular;

};

#endif // RENDERINGWIDGET_H
