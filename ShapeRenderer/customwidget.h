#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QPainter>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:

public slots:

private:
    void paintEvent(QPaintEvent *event) override;

public:
    Qt::BrushStyle GetBrushStyle(int brushtype);
    Qt::PenStyle GetPenStyle(int pentype);
};

#endif // CUSTOMWIDGET_H
