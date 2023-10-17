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
    TaskCardWidget(const QString& title, const QString& complexity, int priority, QWidget* parent = nullptr);

    void mouseMoveEvent(QMouseEvent *event) override;

    QString serializeTaskCardWidget();

    static TaskCardWidget* deserializeTaskCardWidget(const QString& jsonString);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    QLabel* titleLabel;
    QLabel* complexityLabel;
    QLabel* priorityLabel;
};
