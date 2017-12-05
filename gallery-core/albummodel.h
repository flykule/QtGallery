#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include "album.h"
#include "databasemanager.h"
#include "gallery-core_global.h"
#include <QAbstractItemModel>
#include <QHash>
#include <memory>
#include <vector>

// the buffer
using namespace std;

class GALLERYCORESHARED_EXPORT AlbumModel : public QAbstractListModel {
  Q_OBJECT
public:
  enum Roles {
    IdRole = Qt::UserRole + 1,
    NameRole,
  };

  AlbumModel(QObject *parent = 0);

  QModelIndex addAlbum(const Album &album);

  Q_INVOKABLE void addAlbumFromName(const QString &name);

  Q_INVOKABLE void rename(int row, const QString &name);

  Q_INVOKABLE bool deleteAlbum(int row);

  // QAbstractItemModel interface
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role) const override;

  Q_INVOKABLE bool
  removeRows(int row, int count,
             const QModelIndex &parent = QModelIndex()) override;

  bool setData(const QModelIndex &index, const QVariant &value,
               int role) override;

  QHash<int, QByteArray> roleNames() const override;

private:
  bool isIndexValid(const QModelIndex &index) const;

private:
  DatabaseManager &mDb;
  unique_ptr<vector<unique_ptr<Album>>> mAlbums;
};

#endif // ALBUMMODEL_H
