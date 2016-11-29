#include "mainwindow.h"
#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("C:\\Users\\PRANAYUMORYE\\Desktop\\Qt app\\videogui\\ratings.sqlite");

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE ratings(name TEXT PRIMARY KEY, stars INTEGER);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'ratings': one might already exist.";
        success = false;
    }
    else
        success = true;

    return success;
}

bool DbManager::addRating(const QString& path, const int rating)
{
    bool success = false;
    if (!path.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO ratings (name, stars) VALUES (:path, :rating)");
        queryAdd.bindValue(":path", path);
        queryAdd.bindValue(":rating", rating);

        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add track failed: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add track failed: name cannot be empty";
    }

    return success;
}

int DbManager::getRatingOfTrack(QString path)
{
    QSqlQuery query;
    query.prepare("SELECT stars FROM ratings WHERE name = (:path)");
    query.bindValue(":path", path);
    query.exec();

    int idName = query.record().indexOf("stars");
    query.next();
    int rating = query.value(idName).toInt();

    return rating;
}

bool DbManager::setRatingOfTrack(QString path, int rating)
{
    QSqlQuery query;
    query.prepare("UPDATE ratings SET stars= (:stars) WHERE name = (:name)");
    query.bindValue(":stars", rating);
    query.bindValue(":name", path);
    qDebug() << "rating set to " << rating;
    qDebug() << query.exec();

    qDebug() << query.lastError();

    return false;
}

bool DbManager::trackExists(const QString& name) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name FROM ratings WHERE name = (:name)");
    checkQuery.bindValue(":name", name);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "track exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::addTrack(const QString path)
{
    bool success = false;
    if (!path.isEmpty())
    {
        QSqlQuery queryAdd2;
        queryAdd2.prepare("INSERT INTO ratings (name, stars) VALUES (:path, :rating)");
        queryAdd2.bindValue(":path", path);
        queryAdd2.bindValue(":rating", 0);
        if(queryAdd2.exec()) success = true;
    }
    qDebug()<<success;
    return success;
}
