#ifndef PICTUREDAO_H
#define PICTUREDAO_H

#include <QVector>
#include <picture.h>
class QSqlDatabase;
class Picture;
/**
 * @brief The PictureDao class used to do CRUD about picture simliar to
 * @link{AlbumDao} the main difference is that picture has a foreign key album
 * id
 */
class PictureDao {
public:
  explicit PictureDao(QSqlDatabase &database);

  void addPictureInAlbum(int albumId, Picture &picture) const;
  void removePicture(int id) const;
  void removePicturesForAlbum(int albumId) const;
  QVector<Picture *> picturesForAlbum(int albumId) const;
  /**
   * @brief init aims to create picture table when database is opened
   */
  void init() const;

private:
  QSqlDatabase &mDatabase;
};

#endif // PICTUREDAO_H
