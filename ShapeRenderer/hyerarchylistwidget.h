#ifndef HYERARCHYLISTWIDGET_H
#define HYERARCHYLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QString>

namespace Ui {
class HyerarchyListWidget;
}

class HyerarchyListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HyerarchyListWidget(QWidget *parent = 0);
    ~HyerarchyListWidget();

public slots:
    void OnAddEntity();
    void OnDeleteEntity();
    void OnDobleClickEntity();

private:
    Ui::HyerarchyListWidget *ui;

    // For very serious purposes //
    std::vector<QString> entityNames;

public:
    QListWidget* list;

};

#endif // HYERARCHYLISTWIDGET_H
