#include "tablesection.h"
#include <QVBoxLayout>

TableSection::TableSection(QWidget* parent)
    : QWidget(parent)
{
    label = new QLabel("Table Section Label", this);
    customListWidget = new CustomListWidget(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(customListWidget);

    setLayout(layout);
}
