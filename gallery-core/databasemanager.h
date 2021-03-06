#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "albumdao.h"
#include "picturedao.h"
#include <QString>
//提前声明,避免应用此库的所有应用都需要开启sql
class QSqlDatabase;
// database name
const QString DATABASE_FILENAME = "gallery.db";

class QSqlQuery;
class QSqlError;

class DatabaseManager {
public:
  static void debugQuery(const QSqlQuery &query);
  static DatabaseManager &instance();
  ~DatabaseManager();

protected:
  DatabaseManager &operator=(const DatabaseManager &rhs);
  DatabaseManager(const QString &path = DATABASE_FILENAME);

private:
  QSqlDatabase *mDatabase;

public:
  // public to give access to databasemanager client,and const makes
  // no outside modify is allowed
  const AlbumDao albumDao;
  const PictureDao pictureDao;
};

#endif // DATABASEMANAGER_H
