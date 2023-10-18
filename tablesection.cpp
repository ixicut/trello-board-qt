#include "tablesection.h"
#include <QVBoxLayout>

TableSection::TableSection(QString sectionName, QWidget* parent)
    : QWidget(parent)
{
    label = new QLabel(sectionName, this);
    customListWidget = new CustomListWidget(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(customListWidget);
    layout->setContentsMargins(0,0,0,0);

    setLayout(layout);
}
