#include "gallerywidget.h"
#include "ui_gallerywidget.h"

GalleryWidget::GalleryWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::GalleryWidget) {
  ui->setupUi(this);
  connect(&mAlbum, &AlbumWidget::pictureActivated, &mListWidget,
          &AlbumListWidget::createAlbum);
