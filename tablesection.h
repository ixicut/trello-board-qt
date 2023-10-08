#ifndef TABLESECTION_H
#define TABLESECTION_H

#include <QWidget>
#include <QLabel>
#include "customlistwidget.h"

class TableSection : public QWidget
{
    Q_OBJECT

public:
    TableSection(QWidget* parent = nullptr);

private:
    QLabel* label;
    CustomListWidget* customListWidget;
};

#endif // TABLESECTION_H
