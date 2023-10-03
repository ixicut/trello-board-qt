#include <QWidget>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QListWidget>

class TaskCardWidget : public QWidget {
public:
    TaskCardWidget(const QString& name, const QString& surname, int age, QWidget* parent = nullptr)
        : QWidget(parent) {
        setAcceptDrops(true);
        QVBoxLayout* layout = new QVBoxLayout(this);
        nameLabel = new QLabel(name, this);
        surnameLabel = new QLabel(surname, this);
        ageLabel = new QLabel(QString::number(age), this);

        layout->addWidget(nameLabel);
        layout->addWidget(surnameLabel);
        layout->addWidget(ageLabel);

        setLayout(layout);
    }

    QString serializeTaskCardWidget() {
        QJsonObject jsonObject;
        jsonObject["name"] = nameLabel->text();
        jsonObject["surname"] = surnameLabel->text();
        jsonObject["age"] = ageLabel->text().toInt();

        QJsonDocument jsonDoc(jsonObject);
        return jsonDoc.toJson(QJsonDocument::Compact);
    }

    static TaskCardWidget* deserializeTaskCardWidget(const QString& jsonString) {
        QJsonObject jsonObject = QJsonDocument::fromJson(jsonString.toUtf8()).object();
        QString name = jsonObject["name"].toString();
        QString surname = jsonObject["surname"].toString();
        int age = jsonObject["age"].toInt();

        TaskCardWidget* widget = new TaskCardWidget(name, surname, age);
        return widget;
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        QDrag* drag = new QDrag(this->parent()->parent());
        QMimeData* mimeData = new QMimeData();
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);

        mimeData->setData("application/x-qabstractitemmodeldatalist", itemData);
        mimeData->setText(serializeTaskCardWidget());
        drag->setMimeData(mimeData);

        drag->exec(Qt::MoveAction);
    }

    QString getName() {
        return nameLabel->text();
    }

private:
    QLabel* nameLabel;
    QLabel* surnameLabel;
    QLabel* ageLabel;
};
