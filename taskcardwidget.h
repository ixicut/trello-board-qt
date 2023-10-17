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

    QString serializeTaskCardWidget();

    static TaskCardWidget* deserializeTaskCardWidget(const QString& jsonString);

    void updateTaskFields(const QString& title, const QString& complexity, const unsigned int priority);

    QString getTitle();

    QString getComplexity();

    unsigned int getPriority();
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QLabel* titleLabel;
    QLabel* complexityLabel;
    QLabel* priorityLabel;
};
