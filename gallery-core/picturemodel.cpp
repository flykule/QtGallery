#include "picturemodel.h"
#include "album.h"
#include "albummodel.h"
#include "databasemanager.h"

PictureModel::PictureModel(const AlbumModel &albumModel, QObject *parent)
    : QAbstractListModel(parent), mDb(DatabaseManager::instance()),
      mAlbumId(-1), mPictures(new vector<unique_ptr<Picture>>()) {
  connect(&albumModel, &AlbumModel::rowsRemoved, this,
          &PictureModel::deletePicturesForAlbum);
}

QModelIndex PictureModel::addPicture(const Picture &picture) {
  int rowIndex = rowCount();
  beginInsertRows(QModelIndex(), rowIndex, rowIndex);
  unique_ptr<Picture> newPicture(new Picture(picture));
  mDb.pictureDao.addPictureInAlbum(mAlbumId, *newPicture);
  mPictures->emplace_back(move(newPicture));
  endInsertRows();
  return index(rowIndex, 0);
}

void PictureModel::addPictureFromUrl(const QString &url) {
  addPicture(Picture(url));
}

int PictureModel::rowCount(const QModelIndex &parent) const {
  return mPictures->size();
}

QVariant PictureModel::data(const QModelIndex &index, int role) const {
  if (!isIndexValid(index)) {
    return QVariant();
  }
  // deference a unique_ptr to album type;
  const Picture &picture = *mPictures->at(index.row());

  switch (role) {
  case Qt::DisplayRole:
    return picture.fileUrl().fileName();
  case PictureRole::UrlRole:
    return picture.fileUrl();
  case PictureRole::FilePathRole:
    return picture.fileUrl().toLocalFile();
  default:
    return QVariant();
  }
}

bool PictureModel::removeRows(int row, int count, const QModelIndex &parent) {
  if (row < 0 || row >= rowCount() || count < 0 || (row + count) > rowCount()) {
    return false;
  }
  beginRemoveRows(parent, row, row + count - 1);
  int countLeft = count;
  while (countLeft--) {
    const Picture &picture = *mPictures->at(row + countLeft);
    mDb.pictureDao.removePicture(picture.id());
  }
  mPictures->erase(mPictures->begin() + row, mPictures->begin() + row + count);
  endRemoveRows();
  return true;
}

QHash<int, QByteArray> PictureModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[Qt::DisplayRole] = "name";
  roles[PictureRole::FilePathRole] = "filepath";
  roles[PictureRole::UrlRole] = "url";
  return roles;
}

void PictureModel::setAlbumId(int albumId) {
  beginResetModel();
  mAlbumId = albumId;
  loadPictures(mAlbumId);
  endResetModel();
}

void PictureModel::clearAlbum() {
  if (mAlbumId <= 0) {
    return;
  }
  beginResetModel();
  mPictures->clear();
  mDb.pictureDao.removePicturesForAlbum(mAlbumId);
  endResetModel();
}

void PictureModel::deletePicturesForAlbum() { clearAlbum(); }

void PictureModel::loadPictures(int albumId) {
  if (albumId <= 0) {
    mPictures.reset(new vector<unique_ptr<Picture>>());
    return;
  }
  mPictures = mDb.pictureDao.picturesForAlbum(albumId);
}

bool PictureModel::isIndexValid(const QModelIndex &index) const {
  int localRow = index.row();
  return localRow >= 0 && localRow < mPictures->size();
}
