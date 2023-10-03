#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QTabWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customlistwidget.h"
#include "taskcardwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);


    tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);

    QWidget *tab1 = new QWidget(this);
    QWidget *tab2 = new QWidget(this);

    QHBoxLayout *firstTabLayout = new QHBoxLayout(tab1);

    tabWidget->addTab(tab1, "Tab 1");
    tabWidget->addTab(tab2, "Tab 2");

    QListWidget *listWidget1 = new CustomListWidget(this);
    QListWidget *listWidget2 = new CustomListWidget(this);
    QListWidget *listWidget3 = new CustomListWidget(this);

    TaskCardWidget* task1 = new TaskCardWidget("Task 1", "High", 123);
    TaskCardWidget* task2 = new TaskCardWidget("Task 2", "Medium", 678);
    TaskCardWidget* task3 = new TaskCardWidget("Task 3", "High", 234);
    TaskCardWidget* task4 = new TaskCardWidget("Task 4", "Medium", 567);

    QListWidgetItem* item1 = new QListWidgetItem(listWidget1);
    item1->setSizeHint(task1->sizeHint());
    listWidget1->setItemWidget(item1, task1);

    QListWidgetItem* item2 = new QListWidgetItem(listWidget1);
    item2->setSizeHint(task2->sizeHint());
    listWidget1->setItemWidget(item2, task2);

    QListWidgetItem* item3 = new QListWidgetItem(listWidget1);
    item3->setSizeHint(task3->sizeHint());
    listWidget1->setItemWidget(item3, task3);

    QListWidgetItem* item4 = new QListWidgetItem(listWidget1);
    item4->setSizeHint(task4->sizeHint());
    listWidget1->setItemWidget(item4, task4);

    firstTabLayout->addWidget(listWidget1);
    firstTabLayout->addWidget(listWidget2);
    firstTabLayout->addWidget(listWidget3);
}

MainWindow::~MainWindow()
{
    delete ui;
}
