#ifndef PICTURE_H
#define PICTURE_H

#include "gallery-core_global.h"

#include <QUrl>

class GALLERYCORESHARED_EXPORT Picture {
public:
  Picture(const QUrl &fileUrl);
  Picture(const QString &filePath = "");

  int id() const;
  void setId(int id);

  int albumId() const;
  void setAlbumId(int albumId);

  QUrl fileUrl() const;
  void setFileUrl(const QUrl &fileUrl);

private:
  // this picture's id
  int mId;
  // belonged to Album Id
  int mAlbumId;
  QUrl mFileUrl;
};

#endif // PICTURE_H
