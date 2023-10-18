#include "customlistwidget.h"
#include <QDrag>
#include <QDragEnterEvent>
#include <QDataStream>
#include <QMimeData>
#include <QPixmap>
#include <QDebug>
#include <QMenu>
#include "taskcardwidget.h"
#include "createtaskdialog.h"

CustomListWidget::CustomListWidget(QWidget* parent) : QListWidget(parent) {
    setDropIndicatorShown(false);
    setAcceptDrops(true);
}

void CustomListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();

    if (event->proposedAction() == Qt::MoveAction) {
        QListWidget::dragEnterEvent(event);
    }
}

void CustomListWidget::dropEvent(QDropEvent* event)
{
    const QMimeData* data = event->mimeData();

    if (data->hasFormat("application/x-qabstractitemmodeldatalist")) {

        QByteArray itemData = data->data("application/x-qabstractitemmodeldatalist");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString name, surname;
        int age;
        dataStream >> name >> surname >> age;

        QString salo = data->text();

        TaskCardWidget *newTaskCard = TaskCardWidget::deserializeTaskCardWidget(salo);

        QModelIndex index = indexAt(event->pos());

        int dropRow;

        (index.row() == -1) ? dropRow = count() : dropRow = index.row();

        QListWidgetItem* newItem = new QListWidgetItem();
        newItem->setSizeHint(newTaskCard->sizeHint());
        insertItem(dropRow, newItem);
        setItemWidget(newItem, newTaskCard);

        QListWidget::dropEvent(event);

        QListWidget* sourceListWidget = dynamic_cast<CustomListWidget*>(event->source());

        QListWidgetItem * item = sourceListWidget->currentItem();

        sourceListWidget->removeItemWidget(item);
        delete item;

        sourceListWidget->setCurrentItem(newItem);
    }
}

void CustomListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    QAction *action1 = menu.addAction("Create new task");

    connect(action1, &QAction::triggered, this, &CustomListWidget::createTaskHandler);

    menu.exec(event->globalPos());
}

void CustomListWidget::createTaskHandler() {
    CreateTaskDialog taskDialog;
    if (taskDialog.exec() == QDialog::Accepted) {

        QString taskName = taskDialog.getTaskName();
        QString complexity = taskDialog.getComplexity();
        unsigned int priority = taskDialog.getPriority();

        QListWidgetItem* newTaskItem = new QListWidgetItem(this);
        TaskCardWidget* newTask = new TaskCardWidget(taskName, complexity, priority);
        newTaskItem->setSizeHint(newTask->sizeHint());
        this->setItemWidget(newTaskItem, newTask);
    } else {}
}
