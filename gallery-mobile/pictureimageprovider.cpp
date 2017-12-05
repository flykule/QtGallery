#include "pictureimageprovider.h"
#include "picturemodel.h"
#include <QUrl>

// used for cache
const QString PICTURE_SIZE_FULL = "full";
const QString PICTURE_SIZE_THUMBNAIL = "thumbnail";
const QSize PictureImageProvider::THUMBNAIL_SIZE = QSize(350, 350);

PictureImageProvider::PictureImageProvider(PictureModel *pictureModel)
    : QQuickImageProvider(QQuickImageProvider::Pixmap),
      mPictureModel(pictureModel), mPicturesCache() {}

QPixmap PictureImageProvider::requestPixmap(const QString &id, QSize *size,
                                            const QSize &requestedSize) {
  QStringList query = id.split('/');
  if (!mPictureModel || query.size() < 2) {
    return QPixmap();
  }

  int row = query[0].toInt();
  QString pictureSize = query[1];

  QString fileUrl = mPictureModel
                        ->data(mPictureModel->index(row, 0),
                               PictureModel::PictureRole::FilePathRole)
                        .value<QUrl>()
                        .toLocalFile();
  return *pictureFromCache(fileUrl, pictureSize);
}

QPixmap *PictureImageProvider::pictureFromCache(const QString &filepath,
                                                const QString &size) {
  QString key = QStringList{size, filepath}.join("-");
  QPixmap *cachePicture = nullptr;
  if (!mPicturesCache.contains(key)) {
    QPixmap orininalPicture(filepath);
    if (size == PICTURE_SIZE_THUMBNAIL) {
      cachePicture = new QPixmap(orininalPicture.scaled(
          THUMBNAIL_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else if (size == PICTURE_SIZE_FULL) {
      cachePicture = new QPixmap(orininalPicture);
    }
    mPicturesCache.insert(key, cachePicture);
  } else {
    cachePicture = mPicturesCache[key];
  }
  return cachePicture;
}
