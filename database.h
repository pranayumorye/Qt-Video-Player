#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

class DbManager
{
public:
    QString current_path = "";
    /**
     * @brief Constructor
     *
     * Constructor sets up connection with db and opens it
     * @param path - absolute path to db file
     */
    DbManager(const QString& path);

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~DbManager();

    bool isOpen() const;

    /**
     * @brief Creates a new 'people' table if it doesn't already exist
     * @return true - 'people' table created successfully, false - table not created
     */
    bool createTable();

    /**
     * @brief Add track data to db
     * @param name - name of track to add
     * @return true - track added successfully, false - track not added
     */
    bool addTrack(const QString path);

    /**
     * @brief Remove track data from db
     * @param name - name of track to remove.
     * @return true - track removed successfully, false - track not removed
     */

    bool trackExists(const QString& name) const;

    /**
     * @brief Remove all tracks from db
     * @return true - all tracks removed successfully, false - not removed
     */
    bool removeAllTracks();

    bool addRating(const QString &path, const int rating);
    QString getPathOfTrack(QString trackname);
    int getRatingOfTrack(QString path);
    bool setRatingOfTrack(QString path, int rating);
private:
    QSqlDatabase m_db;
};

#endif // DATABASE_H
