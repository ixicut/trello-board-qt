#include "createtaskdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>

CreateTaskDialog::CreateTaskDialog(QWidget *parent)
    : CreateTaskDialog(QString(""),QString(""),1,parent) {}

CreateTaskDialog::CreateTaskDialog(const QString& initialName, const QString& initialComplexity, unsigned int initialPriority, QWidget *parent)
    : QDialog(parent)
{
    nameLineEdit = new QLineEdit(initialName,this);
    complexitySpinBox = new QLineEdit(initialComplexity,this);
    prioritySpinBox = new QSpinBox(this);
    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    prioritySpinBox->setRange(1, 3);
    prioritySpinBox->setValue(static_cast<int>(initialPriority));

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Task Name:", nameLineEdit);
    formLayout->addRow("Complexity:", complexitySpinBox);
    formLayout->addRow("Priority:", prioritySpinBox);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

QString CreateTaskDialog::getTaskName() const
{
    return nameLineEdit->text();
}

QString CreateTaskDialog::getComplexity() const
{
    return complexitySpinBox->text();
}

unsigned int CreateTaskDialog::getPriority() const
{
    return static_cast<unsigned int>(prioritySpinBox->value());
}
