#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QTabWidget>
#include <QAction>
#include <QInputDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskcardwidget.h"
#include "tablesection.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addTableAction, SIGNAL(triggered()), this, SLOT(addNewTabHandler()));
    namelessTabCounter = 0;
    allTabCounter = 0;

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);

    const QString initialTabName = QString("Initial tab");

    createNewTab(initialTabName, true);
}

void MainWindow::createNewTab(const QString &tabTitle, const bool ok){
    QWidget *newTab = new QWidget(this);

    QHBoxLayout *tabLayout = new QHBoxLayout(newTab);

    TableSection *todoTableSection = new TableSection(QString("To do"),this);
    TableSection *inProgressTableSection = new TableSection(QString("In progress"), this);
    TableSection *doneTableSection = new TableSection(QString("Done"), this);

    tabLayout->addWidget(todoTableSection);
    tabLayout->addWidget(inProgressTableSection);
    tabLayout->addWidget(doneTableSection);

    if (ok && !tabTitle.isEmpty()) tabWidget->addTab(newTab, tabTitle);
    else if(ok && tabTitle.isEmpty()) tabWidget->addTab(newTab, "New table " + QString::number(++namelessTabCounter));
    allTabCounter++;
}

void MainWindow::addNewTabHandler() {
    bool ok;
    QString tabTitle = QInputDialog::getText(nullptr, "Enter table name", "Table name:", QLineEdit::Normal, "", &ok);

    createNewTab(tabTitle, ok);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tabWidget;
}
