#include "taskcardwidget.h"

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
    jsonObject["name"] = nameLabel->text();
    jsonObject["surname"] = surnameLabel->text();
    jsonObject["age"] = ageLabel->text().toInt();

    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc.toJson(QJsonDocument::Compact);
}

TaskCardWidget* TaskCardWidget::deserializeTaskCardWidget(const QString& jsonString) {
    QJsonObject jsonObject = QJsonDocument::fromJson(jsonString.toUtf8()).object();
    QString name = jsonObject["name"].toString();
    QString surname = jsonObject["surname"].toString();
    int age = jsonObject["age"].toInt();

    TaskCardWidget* widget = new TaskCardWidget(name, surname, age);
    return widget;
}
