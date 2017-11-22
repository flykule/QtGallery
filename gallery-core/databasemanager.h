#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
//提前声明
class QSqlDatabase;
//表名
const QString DATABASE_FILENAME = "gallery.db";

class DatabaseManager {
public:
  static DatabaseManager &instance();
  ~DatabaseManager();

protected:
  DatabaseManager &operator=(const DatabaseManager &rhs);
  DatabaseManager(const QString &path = DATABASE_FILENAME);

private:
  QSqlDatabase *mDatabase;
};

#endif // DATABASEMANAGER_H
