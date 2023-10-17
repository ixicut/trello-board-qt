#ifndef CREATETASKDIALOG_H
#define CREATETASKDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>

class CreateTaskDialog : public QDialog
{
    Q_OBJECT

public:
    CreateTaskDialog(QWidget *parent = nullptr);
    CreateTaskDialog(const QString& initialName, const QString& initialComplexity, unsigned int initialPriority, QWidget *parent = nullptr);

    QString getTaskName() const;
    QString getComplexity() const;
    unsigned int getPriority() const;

private:
    QLineEdit *nameLineEdit;
    QLineEdit *complexitySpinBox;
    QSpinBox *prioritySpinBox;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif
