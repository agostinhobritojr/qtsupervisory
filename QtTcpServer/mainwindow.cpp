#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myserver.h"
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(&Server,
          SIGNAL(message(QString)),
          this,
          SLOT(showMessage(QString)));
  Server.startServer();
  QStringList list;
  list = Server.getIPList();
  ui->listWidget->addItems(list);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::showMessage(QString msg){
  ui->textBrowser->append(msg);
}

