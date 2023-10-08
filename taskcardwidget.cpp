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
    QDrag* drag = new QDrag(this->parent()->parent());
    QMimeData* mimeData = new QMimeData();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    mimeData->setData("application/x-qabstractitemmodeldatalist", itemData);
    mimeData->setText(serializeTaskCardWidget());
    drag->setMimeData(mimeData);

    drag->exec(Qt::MoveAction);
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
