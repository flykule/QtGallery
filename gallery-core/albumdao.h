#ifndef ALBUMDAO_H
#define ALBUMDAO_H
#include "album.h"
#include <memory>
#include <vector>
// before declare avoid out app to add qt:sql
class QSqlDatabase;

/**
 * @brief The AlbumDao class dedicated to crud for album picture
 */
class AlbumDao {
public:
  /**
   * @brief AlbumDao constructor
   * @param database the database to queries on
   */
  AlbumDao(QSqlDatabase &database);

  /**
   * @brief addAlbum add a new album to database
   * @param album the album to add
   */
  void addAlbum(Album &album) const;
  /**
   * @brief updateAlbum update album in the table if exist
   * @param album the album to find
   */
  void updateAlbum(const Album &album) const;
  /**
   * @brief removeAlbum remove  album with special id
   * @param id the album to be removed's id
   */
  void removeAlbum(int id) const;
  /**
   * @brief albums get all albums in the table or empty vector
   * @return vector of all album in table
   */
  std::unique_ptr<std::vector<std::unique_ptr<Album>>> albums() const;

  /**
   * @brief init aims to create album table when database is opened
   */
  void init() const;

private:
  QSqlDatabase &mDatabase;
};

#endif // ALBUMDAO_H
