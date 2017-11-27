#include "mainwindow.h"
#include "albumlistwidget.h"
#include "albumwidget.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  AlbumWidget *album = new AlbumWidget(this);
  AlbumListWidget *listWidget = new AlbumListWidget(this);

  QHBoxLayout *localQHBoxLayout = new QHBoxLayout();
  localQHBoxLayout->addWidget(listWidget);
  localQHBoxLayout->addWidget(album);
  ui->centralWidget->setLayout(localQHBoxLayout);
}

MainWindow::~MainWindow() { delete ui; }
