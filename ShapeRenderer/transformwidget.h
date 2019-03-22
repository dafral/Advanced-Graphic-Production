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
    void update();
public slots:
    // Name
    void OnNameChanged();
    // Trans
    void OnPosXChanged();
    void OnPosYChanged();
    void OnScaXChanged();
    void OnScaYChanged();
    // Shape
    void OnShapeChanged();
    // Fill Color
    void OnFillColorChanged();
    void OnFillStyleChanged();
    // Stroke
    void OnStrokeColorChanged();
    void OnStrokeThicknessChanged();
    void OnStrokeStyleChanged();
};


#endif // TRANSFORMWIDGET_H
