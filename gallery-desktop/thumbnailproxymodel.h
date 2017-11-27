#ifndef THUMBNAILPROXYMODEL_H
#define THUMBNAILPROXYMODEL_H
#include <QHash>
#include <QIdentityProxyModel>
#include <QPixmap>

class PictureModel;

class ThumbnailProxyModel : public QIdentityProxyModel {
public:
  ThumbnailProxyModel(QObject *parent = 0);

  QVariant data(const QModelIndex &index, int role) const;

  void setSourceModel(QAbstractItemModel *sourceModel);
  PictureModel *pictureModel() const;

private:
  void generateThumbnails(const QModelIndex &startIndex, int count);
  void reloadThumbnails();

private:
  QHash<QString, QPixmap *> mThumbnails;
};

#endif // THUMBNAILPROXYMODEL_H
