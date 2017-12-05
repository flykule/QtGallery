#include "databasemanager.h"
#include <QDebug>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>

void DatabaseManager::debugQuery(const QSqlQuery &query) {
  if (query.lastError().type() == QSqlError::ErrorType::NoError) {
    qDebug() << "Query OK:" << query.lastQuery();
  } else {
    qWarning() << "Query KO:" << query.lastError().text();
    qWarning() << "Query text:" << query.lastQuery();
  }
}

DatabaseManager &DatabaseManager::instance() {

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
  QFile assetDbFile(":/database/" + DATABASE_FILENAME);
  QString destinationDbFile =
      QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)
          .append("/" + DATABASE_FILENAME);
  if (!QFile::exists(destinationDbFile)) {
    assetDbFile.copy(destinationDbFile);
    QFile::setPermissions(destinationDbFile,
                          QFile::WriteOwner | QFile::ReadOwner);
  }
  static DatabaseManager singleton(destinationDbFile);
#else
  static DatabaseManager singleton;
#endif
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
