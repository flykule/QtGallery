#ifndef PICTUREIMAGEPROVIDER_H
#define PICTUREIMAGEPROVIDER_H
#include <QCache>
#include <QQuickImageProvider>

class PictureModel;

class PictureImageProvider : public QQuickImageProvider {
public:
  static const QSize THUMBNAIL_SIZE;
  PictureImageProvider(PictureModel *pictureModel);

  // QQuickImageProvider interface
public:
  QPixmap requestPixmap(const QString &id, QSize *size,
                        const QSize &requestedSize);
  QPixmap *pictureFromCache(const QString &filepath, const QString &size);

private:
  PictureModel *mPictureModel;
  QCache<QString, QPixmap> mPicturesCache;
};

#endif // PICTUREIMAGEPROVIDER_H
