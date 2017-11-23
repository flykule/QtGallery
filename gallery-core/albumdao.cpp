#include "albumdao.h"
#include "databasemanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

AlbumDao::AlbumDao(QSqlDatabase &database) : mDatabase(database) {}

void AlbumDao::addAlbum(Album &album) const {
  QSqlQuery query(mDatabase);
  query.prepare("INSERT INTO albums (name) VALUES (:name)");
  query.bindValue(":name", album.name());
  query.exec();
  album.setId(query.lastInsertId().toInt());
}

void AlbumDao::updateAlbum(const Album &album) const {
  QSqlQuery query(mDatabase);
  query.prepare("UPDATE albums SET name=:name WHERE id=:id");
  query.bindValue(":name", album.name());
  query.bindValue(":id", album.id());
  query.exec();
}

void AlbumDao::removeAlbum(int id) const {
  QSqlQuery query(mDatabase);
  query.prepare("DELETE FROM albums WHERE id=:id");
  query.bindValue(":id", id);
  query.exec();
}

std::unique_ptr<std::vector<std::unique_ptr<Album>>> AlbumDao::albums() const {
  QSqlQuery query(mDatabase);
  query.exec("SELECT * FROM albums");
  std::unique_ptr<std::vector<std::unique_ptr<Album>>> list(
      new std::vector<std::unique_ptr<Album>>());
  while (query.next()) {
    std::unique_ptr<Album> album(new Album());
    album->setName(query.value("name").toString());
    album->setId(query.value("id").toInt());
    list->emplace_back(move(album));
  }
  return list;
}

void AlbumDao::init() const {
  // create table if not exist
  if (!mDatabase.tables().contains("albums")) {
    QSqlQuery query(mDatabase);
    query.exec("CREATE TABLE albums (id INTEGER PIMAREY KEY "
               "AUTOINCREMENT, name TEXT)");
  }
}
