#include "databasemanager.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

void DatabaseManager::debugQuery(const QSqlQuery &query) {
  if (query.lastError().type() == QSqlError::ErrorType::NoError) {
    qDebug() << "Query OK:" << query.lastQuery();
  } else {
    qWarning() << "Query KO:" << query.lastError().text();
    qWarning() << "Query text:" << query.lastQuery();
  }
}

DatabaseManager &DatabaseManager::instance() {
  static DatabaseManager singleton;
  return singleton;
}

DatabaseManager::~DatabaseManager() {
  mDatabase->close();
  delete mDatabase;
}

DatabaseManager::DatabaseManager(const QString &path)
    : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
      albumDao(*mDatabase), pictureDao(*mDatabase) {
  mDatabase->setDatabaseName(path);
  bool localOpen = mDatabase->open();
  qDebug() << "Database connection: " << (localOpen ? "Ok" : "Error");
  albumDao.init();
  pictureDao.init();
}
