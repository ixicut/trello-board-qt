#include <QMenu>
#include "taskcardwidget.h"

TaskCardWidget::TaskCardWidget(const QString& title, const QString& complexity, int priority, QWidget* parent)
    : QWidget(parent) {
    setAcceptDrops(true);
    QVBoxLayout* layout = new QVBoxLayout(this);
    titleLabel = new QLabel(title, this);
    complexityLabel = new QLabel(complexity, this);
    priorityLabel = new QLabel(QString::number(priority), this);

    layout->addWidget(titleLabel);
    layout->addWidget(complexityLabel);
    layout->addWidget(priorityLabel);

    setLayout(layout);
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
    QAction *action1 = menu.addAction("Edit task");
    QAction *action2 = menu.addAction("Delete task");

    connect(action1, &QAction::triggered, this, [&]() {
        // Handle action 1
    });

    connect(action2, &QAction::triggered, this, [&]() {
        // Handle action 2
    });

    menu.exec(event->globalPos());
}
