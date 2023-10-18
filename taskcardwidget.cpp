#include <QMenu>
#include <QMessageBox>
#include "taskcardwidget.h"
#include "customlistwidget.h"
#include "createtaskdialog.h"

TaskCardWidget::TaskCardWidget(const QString& title, const QString& complexity, int priority, QWidget* parent)
    : QWidget(parent) {
    setAcceptDrops(true);
    QLabel *titleCaption = new QLabel("Title: ", this);
    QLabel *complexityCaption = new QLabel("Complexity: ", this);
    QLabel *priorityCaption = new QLabel("Priority: ", this);

    titleLabel = new QLabel(title, this);
    complexityLabel = new QLabel(complexity, this);
    priorityLabel = new QLabel(QString::number(priority), this);

    QGridLayout* gridLayout = new QGridLayout(this);

    // Add widgets to the grid layout
    gridLayout->addWidget(titleCaption, 0, 0);
    gridLayout->addWidget(titleLabel, 0, 1);

    gridLayout->addWidget(complexityCaption, 1, 0);
    gridLayout->addWidget(complexityLabel, 1, 1);

    gridLayout->addWidget(priorityCaption, 2, 0);
    gridLayout->addWidget(priorityLabel, 2, 1);

    setLayout(gridLayout);
}

void TaskCardWidget::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QDrag* drag = new QDrag(this->parent()->parent());
        QMimeData* mimeData = new QMimeData();
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);

        mimeData->setData("application/x-qabstractitemmodeldatalist", itemData);
        mimeData->setText(serializeTaskCardWidget());
        drag->setMimeData(mimeData);

        drag->exec(Qt::MoveAction);
    } else {
        event->ignore();
    }
}

QString TaskCardWidget::serializeTaskCardWidget() {
    QJsonObject jsonObject;
    jsonObject["title"] = titleLabel->text();
    jsonObject["complexity"] = complexityLabel->text();
    jsonObject["priority"] = priorityLabel->text().toInt();

    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc.toJson(QJsonDocument::Compact);
}

TaskCardWidget* TaskCardWidget::deserializeTaskCardWidget(const QString& jsonString) {
    QJsonObject jsonObject = QJsonDocument::fromJson(jsonString.toUtf8()).object();
    QString name = jsonObject["title"].toString();
    QString surname = jsonObject["complexity"].toString();
    int age = jsonObject["priority"].toInt();

    TaskCardWidget* widget = new TaskCardWidget(name, surname, age);
    return widget;
}

void TaskCardWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    QAction *editAction = menu.addAction("Edit task");
    QAction *deleteAction = menu.addAction("Delete task");

    QListWidget* sourceListWidget = dynamic_cast<CustomListWidget*>(this->parent()->parent());
    QListWidgetItem * selectedItem = sourceListWidget->currentItem();

    connect(editAction, &QAction::triggered, this, [&]() {
        TaskCardWidget *retrievedTaskWidget = dynamic_cast<TaskCardWidget*>(sourceListWidget->itemWidget(selectedItem));

        CreateTaskDialog taskDialog =
            CreateTaskDialog(retrievedTaskWidget->getTitle(),retrievedTaskWidget->getComplexity(),retrievedTaskWidget->getPriority());
        if (taskDialog.exec() == QDialog::Accepted) {

            QString taskName = taskDialog.getTaskName();
            QString complexity = taskDialog.getComplexity();
            unsigned int priority = taskDialog.getPriority();

            retrievedTaskWidget->updateTaskFields(taskName,complexity,priority);

        } else {}
    });

    connect(deleteAction, &QAction::triggered, this, [&]() {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Confirm Deletion",
            QString("Are you sure to delete selected task?"),
            QMessageBox::Yes | QMessageBox::No
            );

        if (reply == QMessageBox::Yes) {
            sourceListWidget->removeItemWidget(selectedItem);
            delete selectedItem;
        } else {}
    });

    menu.exec(event->globalPos());
}

void TaskCardWidget::updateTaskFields(const QString& title, const QString& complexity, const unsigned int priority) {
    titleLabel->setText(title);
    complexityLabel->setText(complexity);
    priorityLabel->setText(QString::number(priority));
}

QString TaskCardWidget::getTitle() {
    return titleLabel->text();
}

QString TaskCardWidget::getComplexity() {
    return complexityLabel->text();
}

unsigned int TaskCardWidget::getPriority() {
    return priorityLabel->text().toUInt();
}
