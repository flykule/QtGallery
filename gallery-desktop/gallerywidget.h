#ifndef GALLERYWIDGET_H
#define GALLERYWIDGET_H

#include "albumlistwidget.h"
#include "albumwidget.h"
#include <QWidget>

namespace Ui {
class GalleryWidget;
}

class GalleryWidget : public QWidget {
  Q_OBJECT

public:
  explicit GalleryWidget(QWidget *parent = 0);
  ~GalleryWidget();

  void setAlbumModel(AlbumModel *albumModel);

  void setAlbumSelectionModel(QItemSelectionModel *albumSelectionModel);

  void setPictureModel(ThumbnailProxyModel *pictureModel);

  void setPictureSelectionModel(QItemSelectionModel *pictureSelectionModel);

  void setListWidget(AlbumListWidget *listWidget);

  void setAlbum(AlbumWidget *album);

  AlbumListWidget *listWidget() const;

  AlbumWidget *album() const;

private:
  Ui::GalleryWidget *ui;
  AlbumListWidget *mListWidget;
  AlbumWidget *mAlbum;
};

#endif // GALLERYWIDGET_H
