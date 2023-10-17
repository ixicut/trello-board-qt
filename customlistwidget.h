#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QListWidget>

class CustomListWidget : public QListWidget
{
public:
    CustomListWidget(QWidget* parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
};

#endif // CUSTOMLISTWIDGET_H
