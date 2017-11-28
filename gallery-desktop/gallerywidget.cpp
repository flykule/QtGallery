#include "gallerywidget.h"
#include "ui_gallerywidget.h"

GalleryWidget::GalleryWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::GalleryWidget) {
  ui->setupUi(this);
  ui->albumListWidget->setMaximumWidth(250);
  connect(ui->albumWidget, &AlbumWidget::pictureActivated, this,
          &GalleryWidget::pictureActivated);
}

GalleryWidget::~GalleryWidget() { delete ui; }

void GalleryWidget::setAlbumModel(AlbumModel *albumModel) {
  ui->albumWidget->setAlbumModel(albumModel);
  ui->albumListWidget->setAlbumModel(albumModel);
}

void GalleryWidget::setAlbumSelectionModel(
    QItemSelectionModel *albumSelectionModel) {
  ui->albumListWidget->setSelectionModel(albumSelectionModel);
  ui->albumWidget->setAlbumSelectionModel(albumSelectionModel);
}

void GalleryWidget::setPictureModel(ThumbnailProxyModel *pictureModel) {
  ui->albumWidget->setPictureModel(pictureModel);
}

void GalleryWidget::setPictureSelectionModel(
    QItemSelectionModel *pictureSelectionModel) {
  ui->albumWidget->setPictureSelectionModel(pictureSelectionModel);
}

Ui::GalleryWidget *GalleryWidget::getUi() const { return ui; }
