#include "picturedao.h"
#include "databasemanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

PictureDao::PictureDao(QSqlDatabase &database) : mDatabase(database) {}

void PictureDao::addPictureInAlbum(int albumId, Picture &picture) const {
  QSqlQuery query(mDatabase);
  query.prepare("INSERT INTO pictures (album_id,url) VALUES (:id, :url)");
  query.bindValue(":id", albumId);
  query.bindValue(":url", picture.fileUrl());
  query.exec();
  picture.setId(query.lastInsertId().toInt());
  picture.setAlbumId(albumId);
  DatabaseManager::debugQuery(query);
}

void PictureDao::removePicture(int id) const {
  QSqlQuery query(mDatabase);
  query.prepare("DELETE FROM pictures WHERE id = (:id)");
  query.bindValue(":id", id);
  query.exec();
  DatabaseManager::debugQuery(query);
}

void PictureDao::removePicturesForAlbum(int albumId) const {
  QSqlQuery query(mDatabase);
  query.prepare("DELETE FROM pictures WHERE album_id = (:id)");
  query.bindValue(":id", albumId);
  query.exec();
  DatabaseManager::debugQuery(query);
}

std::unique_ptr<std::vector<std::unique_ptr<Picture>>>
PictureDao::picturesForAlbum(int albumId) const {
  QSqlQuery query(mDatabase);
  query.prepare("SELECT * FROM pictures WHERE album_id = (:id)");
  query.bindValue(":id", albumId);
  query.exec();
  std::unique_ptr<std::vector<std::unique_ptr<Picture>>> list(
      new std::vector<std::unique_ptr<Picture>>());
  while (query.next()) {
    std::unique_ptr<Picture> localPicture(new Picture());
    localPicture->setAlbumId(query.value("album_id").toInt());
    localPicture->setId(query.value("id").toInt());
    localPicture->setFileUrl(query.value("url").toString());
    list->emplace_back(move(localPicture));
  }
  DatabaseManager::debugQuery(query);
  return list;
}

void PictureDao::init() const {
  if (!mDatabase.tables().contains("pictures")) {
    QSqlQuery query(mDatabase);
    query.exec(QString("CREATE TABLE pictures") +
               " (id INTEGER PRIMARY KEY AUTOINCREMENT, " +
               "album_id INTEGER, " + " url TEXT)");
    DatabaseManager::debugQuery(query);
  }
}
