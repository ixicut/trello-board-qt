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

    void mouseMoveEvent(QMouseEvent *event) override;

    QString serializeTaskCardWidget();

    static TaskCardWidget* deserializeTaskCardWidget(const QString& jsonString);

    QString getName() {
        return nameLabel->text();
    }

private:
    QLabel* nameLabel;
    QLabel* surnameLabel;
    QLabel* ageLabel;
};
