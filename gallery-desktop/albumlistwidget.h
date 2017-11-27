#ifndef ALBUMLISTWIDGET_H
#define ALBUMLISTWIDGET_H

#include <QItemSelectionModel>
#include <QWidget>

namespace Ui {
class AlbumListWidget;
}

class AlbumModel;

class AlbumListWidget : public QWidget {
  Q_OBJECT

public:
  explicit AlbumListWidget(QWidget *parent = 0);
  ~AlbumListWidget();

  void setAlbumModel(AlbumModel *albumModel);
  void setSelectionModel(QItemSelectionModel *selectionModel);

private slots:
  void createAlbum();

private:
  Ui::AlbumListWidget *ui;
  AlbumModel *mAlbumModel;
};

#endif // ALBUMLISTWIDGET_H
