#ifndef PICTUREMODEL_H
#define PICTUREMODEL_H

#include "gallery-core_global.h"
#include "picture.h"
#include <QAbstractItemModel>
#include <memory>
#include <vector>

using namespace std;

class Album;
class DatabaseManager;
class AlbumModel;

class GALLERYCORESHARED_EXPORT PictureModel : public QAbstractListModel {
  Q_OBJECT
public:
  enum PictureRole { FilePathRole = Qt::UserRole + 1 };
  PictureModel(const AlbumModel &albumModel, QObject *parent = 0);

  QModelIndex addPicture(const Picture &picture);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  bool removeRows(int row, int count, const QModelIndex &parent) override;

  void setAlbumId(int albumId);
  void clearAlbum();
public slots:
  void deletePicturesForAlbum();

private:
  void loadPictures(int albumId);
  bool isIndexValid(const QModelIndex &index) const;

  DatabaseManager &mDb;
  int mAlbumId;

  unique_ptr<vector<unique_ptr<Picture>>> mPictures;
};

#endif // PICTUREMODEL_H
