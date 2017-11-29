#include "mainwindow.h"
#include "gallerywidget.h"
#include "picturewidget.h"
#include "thumbnailproxymodel.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <albummodel.h>
#include <picturemodel.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      mPictureWidget(new PictureWidget(this)),
      mGalleryWidget(new GalleryWidget(this)),
      mStackedWidget(new QStackedWidget(this)) {

  ui->setupUi(this);

  AlbumModel *album = new AlbumModel(this);
  QItemSelectionModel *albumItemSelectionModel =
      new QItemSelectionModel(album, this);
  mGalleryWidget->setAlbumModel(album);
  mGalleryWidget->setAlbumSelectionModel(albumItemSelectionModel);

  PictureModel *pictureModel = new PictureModel(*album, this);
  ThumbnailProxyModel *thumbnailModel = new ThumbnailProxyModel(this);
  thumbnailModel->setSourceModel(pictureModel);

  QItemSelectionModel *pictureSelectionModel =
      new QItemSelectionModel(thumbnailModel, this);

  mGalleryWidget->setPictureModel(thumbnailModel);
  mGalleryWidget->setPictureSelectionModel(pictureSelectionModel);
  mPictureWidget->setModel(thumbnailModel);
  mPictureWidget->setSelectionModel(pictureSelectionModel);

  connect(mGalleryWidget, &GalleryWidget::pictureActivated, this,
          &MainWindow::displayPicture);
  connect(mPictureWidget, &PictureWidget::backToGallery, this,
          &MainWindow::displayGallery);

  mStackedWidget->addWidget(mGalleryWidget);
  mStackedWidget->addWidget(mPictureWidget);
  displayGallery();

  setCentralWidget(mStackedWidget);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::displayGallery() {
  mStackedWidget->setCurrentWidget(mGalleryWidget);
}

void MainWindow::displayPicture(const QModelIndex &index) {
  mStackedWidget->setCurrentWidget(mPictureWidget);
}
